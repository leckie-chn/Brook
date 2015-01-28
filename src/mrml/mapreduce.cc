// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/mrml/mapreduce.h"

#include "src/base/common.h"
#include "src/base/logging.h"
#include "src/base/scoped_ptr.h"
#include "src/mrml/flags.h"
#include "src/mrml/mappers_and_reducers.h"
#include "src/strutil/split_string.h"
#include "src/strutil/stringprintf.h"

#include <string>
#include <map>
#include <mpi.h>


CLASS_REGISTER_IMPLEMENT_REGISTRY(mapreduce_lite_mapper_registry,
                                  brook::Mapper);

CLASS_REGISTER_IMPLEMENT_REGISTRY(mapreduce_lite_incremental_reducer_registry,
                                  brook::IncrementalReducer);

CLASS_REGISTER_IMPLEMENT_REGISTRY(mapreduce_lite_batch_reducer_registry,
                                  brook::BatchReducer);

namespace brook {

using namespace std;
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
            return false;
        }
    }

    // Create reducer instance.
    if (IAmServerWorker()) {
        GetReducer().reset(CreateReducer());
        if (GetReducer().get() == NULL) {
            return false;
        }
    }

}    

//-----------------------------------------------------------------------------------
// Implementation of ReducerBase:
//-----------------------------------------------------------------------------------
void ReducerBase::Output(const string& key, const string& value) {

}

void ReducerBase::OutputToChannel(int channel,
                                  const string& key, 
                                  const string& value)
{
    
}

const string& ReducerBase::GetOutputFormat() const {
    
}

int ReducerBase::NumOutputChannels() const {
    return 0;
}

//-----------------------------------------------------------------------------------
// Implementation of Mapper
//-----------------------------------------------------------------------------------
int Mapper::Shard(const string& key, int num_reduce_workers) {

}

void Mapper::Output(const string& key, const string& value) {
    
}

void Mapper::OutputToShard(int reduce_shard,
                           const string& key, const string& value)
{

}

void Mapper::OutputToAllShards(const string& key, const string& value) {
    
}

const string& Mapper::CurrentInputFilename() const {

}

const string& Mapper::GetInputFormat() const {
    
}

const string& Mapper::GetOutputFormat() const {

}

int Mapper::GetNumReduceShards() const {
    return 0;
}


} // namespace brook
