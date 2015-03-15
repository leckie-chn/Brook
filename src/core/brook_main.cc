// Copyright : 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
//  The main program of brook project.
//
#include <mpi.h>

#include "src/server/server.h"
#include "src/agent/agent.h"
#include "src/base/common.h"
#include "src/core/flags.h"

#include "gflags/gflags.h"

//-----------------------------------------------------------------------------
// Initialize the brook environment.
//-----------------------------------------------------------------------------

namespace brook {

bool Initialize(int argc, char **argv) {

    // Initialize MPI.
    MPI_Init(&argc, &argv);
    int num_workers = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &num_workers);
    if (num_workers != FLAGS_num_agent_workers + 
                       FLAGS_num_server_workers)
    {
        LOG(ERROR) << "The number of workers [ " << num_workers
                   << " ] does not equal : " << "num_agent [ " 
                   << FLAGS_num_agent_workers << " ] + num_server [ "
                   << FLAGS_num_server_workers << " ]";
        return false;
    }

    return true;
}

bool IAmAgent() {
    int worker_index = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &worker_index);
    return worker_index < FLAGS_num_agent_workers;
}

} // namespace brook

//-----------------------------------------------------------------------------
// The pre-defined main function.
//-----------------------------------------------------------------------------

int main(int argc, char **argv) {
    // Parse command line flags, leaving argc unchanged, but rearrange
    // the arguments in argv so that the flags are all at the beginning.
    google::ParseCommandLineFlags(&argc, &argv, false);

    if (!brook::Initialize(argc, argv)) {
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
