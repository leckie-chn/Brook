// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/mrml/mapreduce.h"

#include "src/base/common.h"
#include "src/base/logging.h"
#include "src/base/scoped_ptr.h"
#include "src/base/filepattern.h"
#include "src/hash/simple_hash.h"
#include "src/mrml/flags.h"
#include "src/mrml/mappers_and_reducers.h"
#include "src/mrml/protofile.h"
#include "src/mrml/protofile.pb.h"
#include "src/mrml/reader.h"
#include "src/strutil/split_string.h"
#include "src/strutil/stringprintf.h"
#include "src/strutil/join_strings.h"
#include "src/sorted_buffer/sorted_buffer.h"
#include "src/sorted_buffer/sorted_buffer_iterator.h"

#include <string>
#include <map>
#include <set>
#include <mpi.h>


#define MPI_TAG_SEND_KEY_VALUE 1

CLASS_REGISTER_IMPLEMENT_REGISTRY(mapreduce_lite_mapper_registry,
                                  brook::Mapper);

CLASS_REGISTER_IMPLEMENT_REGISTRY(mapreduce_lite_incremental_reducer_registry,
                                  brook::IncrementalReducer);

CLASS_REGISTER_IMPLEMENT_REGISTRY(mapreduce_lite_batch_reducer_registry,
                                  brook::BatchReducer);

namespace brook {

using namespace std;
using namespace sorted_buffer;
using std::map;
using std::string;
using std::vector;

//-----------------------------------------------------------------------------------
// MapReduce context, using poor guy's singleton.
//-----------------------------------------------------------------------------------
scoped_ptr<Mapper>& GetMapper() {
    static scoped_ptr<Mapper> mapper;
    return mapper;
}

scoped_ptr<ReducerBase>& GetReducer() {
    static scoped_ptr<ReducerBase> reducer;
    return reducer;
}
 
scoped_ptr<vector<FILE*> >& GetOutputFileDescriptors() {
    static scoped_ptr<vector<FILE*> > output_files(new vector<FILE*>);
    return output_files;
}

scoped_ptr<string>& GetCacheFileValueName() {
    static scoped_ptr<string> cache_file_value_name(new string);
    return cache_file_value_name;
}

scoped_array<char>& GetMapOutputReceiveBuffer() {
    static scoped_array<char> map_output_receive_buffer;
    return map_output_receive_buffer;
}

// Mapper::Output and Mapper::OutputToShard will increase
// this counter once per invocation. Mapper::OutputToAllShards
// increases this counter by the number of server workers.
int g_count_map_output = 0;

//-----------------------------------------------------------------------------------
// Initialization and finalization of Brook
//-----------------------------------------------------------------------------------

bool Initialize(int argc, char** argv) {
    // Initialize MPI 
    MPI_Init(&argc, &argv);

    // Predicates like IAmAgentWorker depends on ValidateCommandLineFlags().
    if (!ValidateCommandLineFlags()) {
        LOG(ERROR) << "Failed validating command line flags.";
        return false;
    }

    // Redirect log message to disk files from terminal. Note that
    // LogFilebase() is valid only after ValidateCommandLineFlags.
    string filename_prefix = LogFilebase();
    InitializeLogger(StringPrintf("%s.INFO", filename_prefix.c_str()),
                     StringPrintf("%s.WARN", filename_prefix.c_str()),
                     StringPrintf("%s.ERROR", filename_prefix.c_str())
                    );

    // Create mapper instance.
    if (IAmAgentWorker()) {
        GetMapper().reset(CreateMapper());
        if (GetMapper().get() == NULL) {
            LOG(ERROR) << "Create Mapper Error.";
            return false;
        }
    }

    // Create reducer instance.
    if (IAmServerWorker()) {
        GetReducer().reset(CreateReducer());
        if (GetReducer().get() == NULL) {
            LOG(ERROR) << "Create Reducer Error.";
            return false;
        }
    }

    // Open output files.
    if (IAmServerWorker()) {
        for (int i = 0 ; i < OutputFiles().size(); ++i) {
            FILE* file = fopen(OutputFiles()[i].c_str(), "w+");
            if (file == NULL) {
                LOG(ERROR) << "Cannot open output file: " << OutputFiles()[i];
                return false;
            }
            GetOutputFileDescriptors()->push_back(file);
        }
    }

    // Create map output receive buffer for server worker.
    if (IAmServerWorker()) {
        try {
            GetMapOutputReceiveBuffer().reset(new char[MapOutputBufferSize()]);
        } catch(std::bad_alloc&) {
            LOG(ERROR) << "Cannot allocation map output receive buffer with size = "
                       << MapOutputBufferSize();
            return false;
        }
    }

    return true;

}    

void Finalize() {
    // After all, finalize MPI.
    MPI_Finalize();
}


//-----------------------------------------------------------------------------------
// Implementation of reduce output facilities.
//
// Used by ReducerBase::Output*
//-----------------------------------------------------------------------------------
void WriteText(FILE* output_stream, const string& key, const string& value) {
    fprintf(output_stream, "%s\t%s\n", key.c_str(), value.c_str());
}

void ReduceOutput(int channel, const string& key, const string& value) {
    CHECK_LE(0, channel);
    CHECK_LT(channel, GetOutputFileDescriptors()->size());

    if (OutputFormat() == "text") {
        WriteText((*GetOutputFileDescriptors())[channel], key, value);
    } else if (OutputFormat() == "protofile") {
        protofile::WriteRecord((*GetOutputFileDescriptors())[channel], key, value);
    }
}

//-----------------------------------------------------------------------------------
// Implementation of map output facilities.
//
// Used by Mapper::Output*
//-----------------------------------------------------------------------------------
void MapOutput(int server_worker_id, const string& key, const string& value) {
    CHECK_LT(server_worker_id, NumServerWorkers());
    // MapOutput format:
    //  message MapOutput {
    //      optional int32 map_worker = 1;
    //      optional bytes key = 2;
    //      optional bytes value = 3;
    //  }
    MapperOutput mo;
    mo.set_key(key);
    mo.set_value(value);
    string smo;
    mo.SerializeToString(&smo);

    MPI_Send(const_cast<char*>(smo.data()), smo.size(), MPI_CHAR,
             server_worker_id, MPI_TAG_SEND_KEY_VALUE,
             MPI_COMM_WORLD);
}

void MapWorkNotifyFinished() {
    MapperOutput mo;
    mo.set_map_worker(WorkerId());
    string smo;
    mo.SerializeToString(&smo);

    for (int recv_id = 0 ; recv_id < ServerWorkers().size() ; recv_id++) {
        MPI_Send(const_cast<char*>(smo.data()), smo.size(), MPI_CHAR, recv_id,
                 MPI_TAG_SEND_KEY_VALUE, MPI_COMM_WORLD);
    }
}

//-----------------------------------------------------------------------------------
// Implementation of ReducerBase:
//-----------------------------------------------------------------------------------
void ReducerBase::Output(const string& key, const string& value) {
    // Used in test
    ReduceOutput(0, key, value);
    // Used in real application
    // Update(key, value);
}

void ReducerBase::OutputToChannel(int channel,
                                  const string& key, 
                                  const string& value)
{
    ReduceOutput(channel, key, value);
}

const string& ReducerBase::GetOutputFormat() const {
    return OutputFormat();
}

int ReducerBase::NumOutputChannels() const {
    return GetOutputFileDescriptors()->size();
}

//-----------------------------------------------------------------------------------
// Implementation of Mapper
//-----------------------------------------------------------------------------------
int Mapper::Shard(const string& key, int num_reduce_workers) {
    return JSHash(key) % num_reduce_workers;
}

void Mapper::Output(const string& key, const string& value) {
    MapOutput(Shard(key, NumServerWorkers()), key, value);
    ++g_count_map_output;
}

void Mapper::OutputToShard(int reduce_shard,
                           const string& key, const string& value)
{
    MapOutput(reduce_shard, key, value);
    ++g_count_map_output;
}

void Mapper::OutputToAllShards(const string& key, const string& value) {
    MapOutput(-1, key, value);
    g_count_map_output += NumServerWorkers();
}

const string& Mapper::CurrentInputFilename() const {
    return *GetCacheFileValueName();
}

const string& Mapper::GetInputFormat() const {
    return InputFormat();
}

int Mapper::GetNumReduceShards() const {
    return NumServerWorkers();
}


//-----------------------------------------------------------------------------------
// Implementation of map worker:
//-----------------------------------------------------------------------------------
void MapWork() {
    LOG(INFO) << "Map work start.";
    // Clear counters.
    g_count_map_output = 0;
    int count_map_input = 0;
    int count_input_shards = 0;

    FilepatternMatcher matcher(CacheFileValuePattern());
    if (!matcher.NoError()) {
        LOG(FATAL) << "Failed matching: " << CacheFileValuePattern();
    }

    for (int i_file = 0 ; i_file < matcher.NumMatched(); ++i_file) {
        *GetCacheFileValueName() = matcher.Matched(i_file);
        LOG(INFO) << "Mapping input file: " << *GetCacheFileValueName();

        scoped_ptr<Reader> reader(CREATE_READER(InputFormat()));
        if (reader.get() == NULL) {
            LOG(FATAL) << "Creating reader for: " << *GetCacheFileValueName();
        }
        reader->Open(GetCacheFileValueName()->c_str());

        GetMapper()->Start();

        string key, value;
        while (true) {
            if (!reader->Read(&key, &value)) {
                break;
            }
            
            GetMapper()->Map(key, value);
            ++count_map_input;
            if ((count_map_input % 10000) == 0) {
                LOG(INFO) << "Processed " << count_map_input << " records.";
            }
        }

        GetMapper()->Flush();
        ++count_input_shards;
        LOG(INFO) << "Finished mapping file: " << *GetCacheFileValueName();
    }
    LOG(INFO) << "Map worker succeeded:\n"
              << " count_map_input = " << count_map_input << "\n"
              << " count_input_shards = " << count_input_shards << "\n"
              << " count_map_output = " << g_count_map_output;

    // Important to tell server workers to terminate.
    MapWorkNotifyFinished();
}


//------------------------------------------------------------------------------------------
// Implementation of reduce worker:
//------------------------------------------------------------------------------------------
void ReduceWork() {
    LOG(INFO) << "Reduce work start.";
    LOG(INFO) << "Output to " << JoinStrings(OutputFiles(), ",");

    // MRML support in addtion "incremental" reduction, where
    // reduce() accepts an intermediate reduce result (represented by a
    // void*, and is NULL for the first value in a reduce input comes)
    // and a reduce value. It should update the intermediate result
    // using the value.
    typedef map<string, void*> PartialReduceResults;
    scoped_ptr<PartialReduceResults> partial_reduce_result;

    // Initialize partial reduce result, or reduce input buffer.
    partial_reduce_result.reset(new PartialReduceResults);

    // In order to Implement the classical MapReduce API, which defineds
    // reduce operator in a "batch" way -- reduce is invoked after
    // all reduce values were collected for a map output key. 
    SortedBuffer* reduce_input_buffer = NULL;

    // Loop over map outputs arrived in this reduce worker.
    LOG(INFO) << "Start receving and processing arriving map outputs ...";
    int32 count_reduce = 0;
    int32 count_map_output = 0;
    int32 recieved_bytes = 0;
    MPI_Status status;

    // Once a agent worker finished processing its input shard, it will
    // send a 'finished' message to all server workers. A server worker
    // collects such messages into finished_agent_worker. After 'finished'
    // message from all map worker are collected, the reduce worker quits.
    std::set<int> finished_agent_worker;

    while (true) {
        MPI_Recv(GetMapOutputReceiveBuffer().get(),
                 MapOutputBufferSize(),
                 MPI_CHAR,
                 MPI_ANY_SOURCE,
                 MPI_TAG_SEND_KEY_VALUE,
                 MPI_COMM_WORLD,
                 &status);

        MPI_Get_count(&status, MPI_CHAR, &recieved_bytes);

        if (recieved_bytes >= MapOutputBufferSize()) {
            LOG(FATAL) << "MPI_Recieving a proto message with size (at least) "
                       << recieved_bytes
                       << ", which >= FLAGS_max_map_output_size ( "
                       << MapOutputBufferSize() << " )."
                       << "You can modify FLAGS_max_map_output_size defined in "
                       << "src/mrml/flags.cc";
        }

        MapperOutput mo;
        CHECK(mo.ParseFromArray(GetMapOutputReceiveBuffer().get(),
                                recieved_bytes));

        if (mo.has_map_worker()) {
            finished_agent_worker.insert(mo.map_worker());
            if (finished_agent_worker.size() >= NumAgentWorkers()) {
                LOG(INFO) << "Finished receving and processing arriving map outputs";
                break; // Brea the while (true) {} Loop.
            }
        } else {
            CHECK(mo.has_key());
            CHECK(mo.has_value());
            ++count_map_output;
            
            if (!BatchReduction()) {
                // Begin a new reduce, which insert a partial result, or does
                // partial reduce, which updates a partial result.
                PartialReduceResults::iterator iter = 
                   partial_reduce_result->find(mo.key());
                if (iter == partial_reduce_result->end()) {
                    (*partial_reduce_result)[mo.key()] = 
                        reinterpret_cast<IncrementalReducer*>(GetReducer().get())->
                        BeginReduce(mo.key(), mo.value());
                } else {
                    reinterpret_cast<IncrementalReducer*>(GetReducer().get())->
                    PartialReduce(mo.key(), mo.value(), iter->second);
                }
    
                if ((count_map_output % 10000) == 0) {
                    LOG(INFO) << "Processed " << count_map_output << " map outputs.";
                }
            } else {
                // Insert the map output into disk buffer.
                reduce_input_buffer->Insert(mo.key(), mo.value());
            }
        }
    }

    // Invoke EndReduce in incremental reduction model, or invoke Reduce
    // int batch reduction mode.
    if (!BatchReduction()) {
        LOG(INFO) << "Finalizing incremental reduction ...";
        for (PartialReduceResults::const_iterator iter = 
                partial_reduce_result->begin();
            iter != partial_reduce_result->end(); ++iter)
        {
            reinterpret_cast<IncrementalReducer*>(GetReducer().get())->
               EndReduce(iter->first, iter->second);
            // Note: deleting of iter->second must be performed by the user
            // program in EndReduce, because mapreduce.cc dose not know the type of
            // ReducePartialResult defined by the user program;
            ++count_reduce;
        }
        LOG(INFO) << "Succeeded finalizing incremental reduction.";
    } else {
        /*
        reduce_input_buffer->Flush();
        LOG(INFO) << "Start batch reduction ...";
        SortedBufferIteratorImpl* reduce_input_buffer_iterator = 
        reinterpret_cast<SortedBufferIteratorImpl*>(
            reduce_input_buffer->CreateIterator());
        */
    }


    LOG(INFO) << " count reduce = " << count_reduce << "\n"
              << " count_map_output = " << count_map_output << "\n";

    GetReducer().get()->Flush();

}


} // namespace brook
