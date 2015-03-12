// Copyright : 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/base/common.h"
#include "gflags/gflags.h"
#include "src/agent/agent.h"

int main (int argc, char **argv) {
    
    // Parse command Line flags, Leaving argc unchanged, but rearrange
    // the arguments in argv so that the flags are all at the beginning.
    google::ParseCommandLineFlags(&argc, &argv, false);

    if (!brook::Agent_Initialize()) {
        LOG(ERROR) << "Initialization of agent service failed.";
        return -1;
    }

    brook::Agent_Service();
    brook::Agent_Finalize();

    return 0;
}

