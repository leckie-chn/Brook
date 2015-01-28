// Copyright 2014 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
//  Define flags used by agent / server to accept instructions from
//  scheduler.
//
#include "src/mrml/flags.h"

#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>

#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <mpi.h>

#include "src/base/common.h"
#include "src/base/scoped_ptr.h"
#include "gflags/gflags.h"
#include "src/mrml/mapreduce.h"
#include "src/strutil/stringprintf.h"
#include "src/strutil/split_string.h"


namespace brook {

const int kDefaultMapOutputSize = 32 * 1024 * 1024; // 32MB

DEFINE_int32(num_agent_workers, 0,
             "The number of agent workers, required by server workers to "
             "check whether all agent workers had finished their work. This ");

DEFINE_int32(num_server_workers, 0,
             "The number of server workers, required bt agent workers to "
             "check whether all server workers had finished their work. This ");

DEFINE_string(agent_workers, "",
             "The set of agent workers, identified by a zero-based number"
             "such as '1:2:3:4'"
             "This flag is set for agent and server, to let them know who they are.");

DEFINE_string(server_workers, "",
             "A set of server workers, identified by a zero-based number"
             "such as '7:8:9'"
             "This flag is set for agent and server, to let them know who they are.");

DEFINE_string(mapper_class, "",
             "This flag is set only for agent workers to let them know the"
             "mapper class that they should execute. Note that this flag "
             "implies that each map worker can execute only one mapper "
             "class in its life. This might be changed in the future when we "
             "support better work load balance.");

DEFINE_string(reducer_class, "",
             "This flag is set only for server workers to let them know the "
              "reducer class that they should execute.");

DEFINE_string(cache_file_value, "",
             "A cache file which store the sub value that generated by user program."
             "Agent worker read from this file.");

DEFINE_string(cache_file_model, "",
             "A cache file which store the model that generator by agent."
             "Agent worker write to this file.");

DEFINE_string(output_files, "",
             "A server worker may generator one or more "
             "output files, each for a server output channel. Usually there "
             "is only one output channel, thus one output file per worker.");

DEFINE_string(input_format, "text",
             "The input format, can be either \"text\", \"recordio\", or \"protofile\". "
             "This flag is set only for agent workers.");

DEFINE_string(output_format, "text",
             "The output format, can be either \"text\", \"recordio\", or \"protofile\"."
             "This flag is set only for server workers.");

DEFINE_string(log_filebase, "",
             "The real log filename is log_filebase appended by worker "
             "type, worker id, date, time, process_id, log type and etc.");

DEFINE_int32(max_map_output_size,
             brook::kDefaultMapOutputSize,
             "The max size of a map output, in bytes.");

//------------------------------------------------------------------------------------------------
// Poor guy's singletons:
//------------------------------------------------------------------------------------------------
typedef std::vector<std::string> StringVector;
typedef std::vector<uint16> IntVector;


static scoped_ptr<IntVector>& GetServerWorkers() {
    static scoped_ptr<IntVector> server_workers(new IntVector);
    return server_workers;
}

static scoped_ptr<IntVector>& GetAgentWorkers() {
    static scoped_ptr<IntVector> agent_workers(new IntVector);
    return agent_workers;
}

static scoped_ptr<StringVector>& GetOutputFiles() {
    static scoped_ptr<StringVector> output_files(new StringVector);
    return output_files;
}


//------------------------------------------------------------------------------------------------
// Flag accessors.
//------------------------------------------------------------------------------------------------
bool IAmAgentWorker() {
    int worker_index = -1;
    MPI_Comm_rank(MPI_COMM_WORLD, &worker_index);
    CHECK_GE(worker_index, 0);
    for (int i = 0 ; i < GetServerWorkers()->size() ; i++) {
        if ((*(GetServerWorkers().get()))[i] == worker_index) {
            return false;
        }
    }

    return true;
}

bool IAmServerWorker() {
    return !IAmAgentWorker();
}

const char* WorkerType() {
    return IAmAgentWorker() ? "agent" : "server";
}

int WorkerId() {
    int worker_index = -1;
    MPI_Comm_rank(MPI_COMM_WORLD, &worker_index);
    CHECK_GE(worker_index, 0);
    return worker_index;
}

int NumAgentWorkers() {
    return FLAGS_num_agent_workers;
}

int NumServerWorkers() {
    return FLAGS_num_server_workers;
}

int NumWorkers() {
    return IAmAgentWorker() ? NumAgentWorkers() : NumServerWorkers();
}

const std::string& GetMapperClass() {
    return FLAGS_mapper_class;
}

const std::string& GetReducerClass() {
    return FLAGS_reducer_class;
}

const std::string& OutputFormat() {
    return FLAGS_output_format;
}

const std::string& InputFormat() {
    return FLAGS_input_format;
}

const IntVector& ServerWorkers() {
    return *GetServerWorkers();
}

const IntVector& AgentWorkers() {
    return *GetAgentWorkers();
}

const StringVector& OutputFiles() {
    return *GetOutputFiles();
}

const std::string& CacheFileValuePattern() {
    return FLAGS_cache_file_value;
}

const std::string& CacheFileModelPattern() {
    return FLAGS_cache_file_model;
}

std::string GetHostName() {
    struct utsname buf;
    if (0 != uname(&buf)) {
        *buf.nodename = '\0';
    }
    return std::string(buf.nodename);
}

std::string GetUserName() {
    const char* username = getenv("USER");
    return username != NULL ? username : getenv("USERNAME");
}

std::string PrintCurrentTime() {
    time_t current_time = time(NULL);
    struct tm broken_down_time;
    CHECK(localtime_r(&current_time, &broken_down_time) == &broken_down_time);
    return StringPrintf("%04d%02d%02d-%02d%02d%02d",
                        1900 + broken_down_time.tm_year,
                        1 + broken_down_time.tm_mon,
                        broken_down_time.tm_mday,
                        broken_down_time.tm_hour,
                        broken_down_time.tm_min,
                        broken_down_time.tm_sec);
}

int MapOutputBufferSize() {
    return FLAGS_max_map_output_size;
}

std::string LogFilebase() {
    // log_filebase := FLAGS_log_filebase + 
    //                 worker_type + worker_index + total_worker_num
    //                 node_name + username +
    //                 date_time + process_id
    CHECK(!FLAGS_log_filebase.empty());
    std::string filename_prefix;
    SStringPrintf(&filename_prefix,
                  "%s-%s-%05d-of-%05d.%s.%s.%s.%u",
                  FLAGS_log_filebase.c_str(),
                  WorkerType(), WorkerId(), NumWorkers(),
                  GetHostName().c_str(),
                  GetUserName().c_str(),
                  PrintCurrentTime().c_str(),
                  getpid());

    return filename_prefix;
}

void ChangeStringListToIntList(StringVector& str_list, 
                               IntVector& int_list)
{
    for (int i = 0 ; i < str_list.size() ; i++) {
        int_list.push_back(atoi(str_list[i].c_str()));
    }
}

//------------------------------------------------------------------------------------------------
// Check the correctness of flags.
//------------------------------------------------------------------------------------------------
bool ValidateCommandLineFlags() {
    bool flags_valid = true;

    // check the number of server workers. Validates NumServerWorkers();
    StringVector workers_;
    SplitStringUsing(FLAGS_server_workers, ",", &workers_);
    ChangeStringListToIntList(workers_,* (GetServerWorkers().get()));
    if (GetServerWorkers()->size() != FLAGS_num_server_workers) {
        LOG(ERROR) << "num server worker set error.";
        flags_valid = false;
    }

    // check the number of agent workers. Validates NumAgentWorkers().
    workers_.clear();
    SplitStringUsing(FLAGS_agent_workers, ",", &workers_);
    ChangeStringListToIntList(workers_, *(GetAgentWorkers().get()));
    if (GetAgentWorkers()->size() != FLAGS_num_agent_workers) {
        LOG(ERROR) << "num agent worker set error.";
        flags_valid = false;
    }

    // If input file format is unknow, set it to text.
    if (FLAGS_input_format != "text" &&
        FLAGS_input_format != "recordio" &&
        FLAGS_input_format != "protofile")
    {
        LOG(ERROR) << "Unknow input_format: " << FLAGS_input_format;
        flags_valid = false;
    }

    // If output file format is unknow, set it to text.
    if (FLAGS_output_format != "text" &&
        FLAGS_output_format != "recordio" &&
        FLAGS_output_format != "protofile") 
    {
        LOG(ERROR) << "Unknow output_format: " << FLAGS_output_format;
        flags_valid = false;
    }

    // Agent worker must be cache_file_value specified.
    if (IAmAgentWorker()) {
        if (FLAGS_cache_file_value.empty()) {
            LOG(ERROR) << "For a agent worker, cache_file_value must be setted.";
            flags_valid = false;
        }
    }

    // Agent worker must be cache_file_model specified.
    if (IAmAgentWorker()) {
        if (FLAGS_cache_file_model.empty()) {
            LOG(ERROR) << "For a agent worker, cache_file_value must be setted.";
            flags_valid = false;
        }
    }

    // Server worker must be output_files specified.
    if (!IAmAgentWorker()) {
        SplitStringUsing(FLAGS_output_files, ",", GetOutputFiles().get());
        if (GetOutputFiles()->size() <= 0) {
            LOG(ERROR) << "For a server worker, output file must be setted.";
            flags_valid = false;
        }
    }

    // Agent worker must be mapper_class specified.
    if (IAmAgentWorker()) {
        if (FLAGS_mapper_class.empty()) {
            LOG(ERROR) << "Mapper class must be setted.";
            flags_valid = false;
        }
    }

    // Server worker must be reducer_class specified.
    if (!IAmAgentWorker()) {
        if (FLAGS_reducer_class.empty()) {
            LOG(ERROR) << "Reducer class must be setted.";
            flags_valid = false;
        }
    }

    // Log filebase must be specified.
    if (FLAGS_log_filebase.empty()) {
        LOG(ERROR) << "Log file base must be specified.";
        flags_valid = false;
    }
    
    return flags_valid;
}

Mapper* CreateMapper() {
    Mapper* mapper = NULL;
    if (IAmAgentWorker()) {
        mapper = CREATE_MAPPER(FLAGS_mapper_class);
        if (mapper == NULL) {
            LOG(ERROR) << "Cannot create mapper: " << FLAGS_mapper_class;
        }
    }
    return mapper;
}

ReducerBase* CreateReducer() {
    ReducerBase* reducer = NULL;
    if (IAmAgentWorker()) {
        reducer = reinterpret_cast<ReducerBase*>(
            CREATE_INCREMENTAL_REDUCER(FLAGS_reducer_class)
        );
        if (reducer == NULL) {
            LOG(ERROR) << "Cannot create reducer: " << FLAGS_reducer_class;
        }
    }
    return reducer;
}

} // namespac brook
