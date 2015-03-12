// Copyright : 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/agent/agent.h"
#include "src/agent/flags.h"

#include "src/base/logging.h"

namespace brook {

//-------------------------------------------------------------------
// Initialization of agent
//-------------------------------------------------------------------
bool Agent_Initialize() {
    if (!ValidateCommandLineFlags()) {
        LOG(ERROR) << "Failed validating command line flags.";
        return false;
    }

    return true;
}

//-------------------------------------------------------------------
// Finalization of agent
//-------------------------------------------------------------------
void Agent_Finalize() {

}

//-------------------------------------------------------------------
// Agent service
//-------------------------------------------------------------------
void Agent_Service() {

}

} // namespace brook
