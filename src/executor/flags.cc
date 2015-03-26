// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
// Define the flags used by brook system to accept instructions from
// scheduler.
//
#include "src/executor/flags.h"

#include <mpi.h>

#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "boost/filesystem.hpp"

#include "src/util/common.h"
#include "src/util/scoped_ptr.h"
#include "gflags/gflags.h"
#include "src/util/stringprintf.h"
#include "src/util/split_string.h"

namespace brook {

const int kDefaultAgentOutputSize = 64 * 1024 * 1024; // 64 MB

} // namespace brook

DEFINE_int32(num_agent_workers, 0, 
             "The num of agent workers.");

DEFINE_int32(num_server_workers, 0, 
             "The num of server workers.");

DEFINE_int64(max_features, 0,
             "The max num of features.");

DEFINE_string(cache_file_update, "", 
              "The file pattern of updating cache file.");

DEFINE_string(cache_file_parameter, "", 
              "The file pattern of parameter cache file.");

DEFINE_string(signal_file_update, "",
              "The file name of updating signal fifo file.");

DEFINE_string(signal_file_parameter, "",
              "The file name of parameter signal fifo file.");

DEFINE_string(log_filebase, "",
              "The real log filename is log_filebase appended by worker "
              "type, worker id, date, time, process_id, log type and etc.");

DEFINE_int32(max_agent_output_size,
             brook::kDefaultAgentOutputSize,
             "The max size of a agent output, in bytes.");

namespace brook {

typedef std::vector<std::string> StringVector;

int TotalWorkerNum() {
    int num = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &num);
    return num;
}

//----------------------------------------------------------------------------
// Check the correctness of flags.
//----------------------------------------------------------------------------

bool ValidateCommandLineFlags() {
    bool flags_valid = true;
    
    // Check positive number of agent workers. 
    if (FLAGS_num_agent_workers <= 0) {
        LOG(ERROR) << "num_agent_workers must be a positive value.";
        flags_valid = false;
    }
    // Check positive number of server worker.
    if (FLAGS_num_server_workers <= 0) {
        LOG(ERROR) << "num_server_workers must be a positive value.";
        flags_valid = false;
    }
    // Check agent + server = total - 1
    if (FLAGS_num_agent_workers + FLAGS_num_server_workers != TotalWorkerNum() - 1) {
        LOG(ERROR) << "num_agent_workers + num_server_workers != TotalWorkerNum - 1";
        flags_valid = false;
    }

    // Check positive number of max_features
    if (FLAGS_max_features <= 0) {
        LOG(ERROR) << "max_features must ve a positive value.";
        flags_valid = false;
    }

    // Check cache_file_update
    if (FLAGS_cache_file_update.empty()) {
        LOG(ERROR) << "cache_file_update must be specified.";
        flags_valid = false;
    }

    // Check cache_file_parameter
    if (FLAGS_cache_file_parameter.empty()) {
        LOG(ERROR) << "cache_file_parameter must be specified.";
        flags_valid = false;
    }

    // Check signal_file_update
    if (FLAGS_signal_file_update.empty()) {
        LOG(ERROR) << "signal_file_update must be specified.";
        flags_valid = false;
    }

    // Check signal_file_parameter
    if (FLAGS_signal_file_parameter.empty()) {
        LOG(ERROR) << "signal_file_parameter must be specified.";
        flags_valid = false;
    }

    // Check log_filebase
    if (FLAGS_log_filebase.empty()) {
        LOG(ERROR) << "log_filebase must be specified.";
        flags_valid = false;
    }

    return flags_valid;
}

int WorkerID() {
    int num = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &num);
    return num;
}

int NumAgent() {
    return FLAGS_num_agent_workers;
}

int NumServer() {
    return FLAGS_num_server_workers;
}

int64 MaxFeatures() {
    return FLAGS_max_features;
}

std::string WorkerType() {
    return WorkerID() > NumAgent() ? "Server" : 
           (WorkerID == 0 ? "Master" : "Agent");
}

const std::string Cache_file_update() {
    return FLAGS_cache_file_update;
}

const std::string Cache_file_parameter() {
    return FLAGS_cache_file_parameter;
}

const std::string Signal_file_update() {
    return FLAGS_signal_file_update;
}

const std::string Signal_file_parameter() {
    return FLAGS_signal_file_parameter;
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

const std::string LogFilebase() {
    // log_filebase := FLAGS_log_filebase +
    //                 worker_type + worker_index + total_worker_num
    //                 node_name + username +
    //                 date_time + process_id
    std::string filename_prefix;
    SStringPrintf(&filename_prefix,
                  "%s-%s-%05d-of-%05d.%s.%s.%s.%u",
                  FLAGS_log_filebase.c_str(),
                  WorkerType().c_str(), WorkerID(), 
                  TotalWorkerNum(),
                  GetHostName().c_str(),
                  GetUserName().c_str(),
                  PrintCurrentTime().c_str(),
                  getpid());
    return filename_prefix;
}

int Shard(uint64 index) {
    return index / FLAGS_max_features * FLAGS_num_server_workers 
                 + FLAGS_num_agent_workers + 1;
}


} // namespace brook;

