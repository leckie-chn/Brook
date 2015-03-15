// Copyright : 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
// Define flags used by agent workers to accept instructions
// from brook scheduler.
//
#ifndef AGENT_FLAGS_H_
#define AGENT_FLAGS_H_

#include <string>
#include <vector>

#include "gflags/gflags.h"

namespace brook {


DECLARE_int32(num_agent_workers);
DECLARE_int32(num_server_workers);

} // namespace brook

#endif // AGENT_FLAGS_H_
