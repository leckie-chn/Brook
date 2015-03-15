// Copyright : 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
// Define flags used by agent workers to accept instructions
// from brook scheduler.
//
#include "src/agent/flags.h"

#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "boost/filesystem.hpp"

#include "src/base/common.h"
#include "src/base/scoped_ptr.h"
#include "gflags/gflags.h"
#include "src/sorted_buffer/sorted_buffer.h"
#include "src/strutil/stringprintf.h"
#include "src/strutil/split_string.h"

namespace brook {

DEFINE_int32(num_agent_workers, -1,
             "");

DEFINE_int32(num_server_workers, -1,
             "");




} // namespace
