// Copyright : 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/agent/agent.h"

#include <mpi.h>

#include <stdio.h>

#include <map>
#include <new>
#include <string>
#include <vector>

#include "src/main/flags.h"
#include "src/base/scoped_ptr.h"
#include "src/base/common.h"
#include "src/message/message.pb.h"

namespace brook {

using std::map;
using std::string;
using std::vector;

bool AgentInitialize() {

    return true;
}

void AgentService() {

    if (!AgentInitialize()) {
        LOG(FATAL) << "Agent initialize failed.";
    }

    LOG(INFO) << "Agent service started!";

    // TEST
    
    // TEST

    AgentFinalize();
}    

void AgentFinalize() {
    
    LOG(INFO) << "Agent Finalize.";
}

} // namespace brook
