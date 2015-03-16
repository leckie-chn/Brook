// Copyright : 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
// Define flags used by agent workers to accept instructions
// from brook scheduler.
//
#include <mpi.h>

#include "src/core/flags.h"

#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "src/base/common.h"
#include "src/base/scoped_ptr.h"
#include "gflags/gflags.h"
#include "src/sorted_buffer/sorted_buffer.h"
#include "src/strutil/stringprintf.h"
#include "src/strutil/split_string.h"


DEFINE_int32(num_agent_workers, -1,
             "The number of agent workers.");

DEFINE_int32(num_server_workers, -1,
             "The number of server workers.");

DEFINE_bool(sorted_shuffle, false,
            "Brook support two kinds of shuffle : sorted_based_shuffle and "
            "hash_based_shuffle. By default, Brook works in hash_based_shuffle.");

DEFINE_string(model_cache_file, "",
             "The name of the in memory file, to which the agent workers " 
             "write model.");

DEFINE_string(subdata_cache_file, "",
              "The name of the in memory file, from which the agent workers "
              "read sub data.");

DEFINE_string(model_fifo_file, "",
              "The name of the model signal fifo file.");

DEFINE_string(subdata_fifo_file, "",
              "The name of the subdata signal fifo file.");

DEFINE_string(output_files, "",
              "The name of the output file, which the server write parameter data to it.");

DEFINE_string(output_format, "text",
              "The output format, can be either 'text' or 'recordio'.");

DEFINE_string(log_filebase, "",
              "The real log filename is log_filebase appended by worker "
              "type, worker id, date, time, process_id, log type and etc");

DEFINE_int64(num_features, -1,
             "The num of feature vector. Used by partition.");

namespace brook {

//----------------------------------------------------------------------------
// Check the correctness of flags.
//----------------------------------------------------------------------------

bool ValidateCommandLineFlags() {

    bool flags_valid = true;

    int num_workers = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &num_workers);
    if (num_workers != FLAGS_num_agent_workers + 
                       FLAGS_num_server_workers)
    {
        LOG(ERROR) << "The number of workers [ " << num_workers
                   << " ] does not equal : " << "num_agent [ "
                   << FLAGS_num_agent_workers << " ] + num_server [ "
                   << FLAGS_num_server_workers << " ]";
        flags_valid = false;
    }

    if (FLAGS_model_cache_file.empty()) {
        LOG(ERROR) << "model_cache_file must be specified.";
        flags_valid = false;
    }

    if (FLAGS_subdata_cache_file.empty()) {
        LOG(ERROR) << "subdata_cache_file must be specified.";
        flags_valid = false;
    }

    if (FLAGS_model_fifo_file.empty()) {
        LOG(ERROR) << "model_fifo_file must be specified.";
        flags_valid = false;
    }

    if (FLAGS_subdata_fifo_file.empty()) {
        LOG(ERROR) << "subdata_fifo_file must be specified.";
        flags_valid = false;
    }

    if (FLAGS_output_files.empty()) {
        LOG(ERROR) << "output_files must be specified.";
        flags_valid = false;
    }

    if (FLAGS_log_filebase.empty()) {
        LOG(ERROR) << "log_filebase must be specified.";
    }

    if (FLAGS_num_features <= 0) {
        LOG(ERROR) << "num_features must be a positive number.";
    }

    return flags_valid;
}

//-----------------------------------------------------------
// Flag accessors.
//-----------------------------------------------------------

int NumAgentWorkers() {
    return FLAGS_num_agent_workers;
}

int NumServerWorkers() {
    return FLAGS_num_server_workers;
}

int NumWorkers() {
    int num_workers = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &num_workers);
    return num_workers;
}

int WorkerId() {
    int worker_index = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &worker_index);
    return worker_index;
}

bool IAmAgent() {
    return WorkerId() < NumAgentWorkers();
}

const char* WorkerType() {
    return IAmAgent() ? "agent" : "server";
}

bool SortBasedShuffle() {
    return FLAGS_sorted_shuffle;
}

std::string ModelCacheFile() {
    return FLAGS_model_cache_file;
}

std::string SubDataCacheFile() {
    return FLAGS_subdata_cache_file;
}

std::string ModelFIFOFile() {
    return FLAGS_model_fifo_file;
}

std::string SubDataFIFOFile() {
    return FLAGS_subdata_fifo_file;
}

std::string OutputFormat() {
    return FLAGS_output_format;
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
                        broken_down_time.tm_mday, broken_down_time.tm_hour,
                        broken_down_time.tm_min, broken_down_time.tm_sec);
}

std::string LogFilebase() {
    // log_filebase := FLAGS_log_filebase + 
    //                 worker_type + worker_index + total_worker_num
    //                 node_name + username +
    //                 date_time + process_id
    CHECK(!FLAGS_log_filebase.empty());
    std::string filename_prefix;
    SStringPrintf(&filename_prefix,
                  "%s-%s-%05d-of-%05d.%d.%s.%s.%u",
                  FLAGS_log_filebase.c_str(),
                  WorkerType(), WorkerId(), NumWorkers(),
                  GetHostName().c_str(),
                  GetUserName().c_str(),
                  PrintCurrentTime().c_str(),
                  getpid());
    return filename_prefix;
}

int64 NumFeatures() {
    return FLAGS_num_features;
}

} // namespace brook
