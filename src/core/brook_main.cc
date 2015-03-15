// Copyright : 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
//  The main program of brook project.
//
#include "src/server/server.h"
#include "src/agent/agent.h"
#include "src/base/common.h"

#include "gflags/gflags.h"

namespace brook {
    bool IAmAgent();
    void AgentService();
    void ServerService();
} // namespace brook

//-----------------------------------------------------------------------------
// The pre-defined main function
//-----------------------------------------------------------------------------

bool Initialize() {

    return true;
}

int main(int argc, char **argv) {
    // Parse command line flags, leaving argc unchanged, but rearrange
    // the arguments in argv so that the flags are all at the beginning.
    google::ParseCommandLineFlags(&argc, &argv, false);

    if (!Initialize()) {
        LOG(ERROR) << "Initialization of Brook failed.";
        return -1;
    }

    LOG(INFO) << "I am a " << (brook::IAmAgent() ? "agent worker" : 
                              "server worker.");

    if (brook::IAmAgent()) {
        brook::AgentService();
    }
    else {
        brook::ServerService();
    }

    return 0;
}
