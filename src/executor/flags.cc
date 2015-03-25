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

DEFINE_int32
