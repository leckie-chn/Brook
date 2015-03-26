// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
// Define the flags used by brook system to accept instructions from
// scheduler.
//
#include "src/executor/flags.h"

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

//----------------------------------------------------------------------------
// Check the correctness of flags.
//----------------------------------------------------------------------------

bool ValidateCommandLineFlags() {

}

} // namespace brook;

