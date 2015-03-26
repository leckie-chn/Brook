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

std::string WorkerType() {
        
     return "";
}

} // namespace brook;

