// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include <string>

#include "src/util/common.h"
#include "gflags/gflags.h"
#include "src/executor/flags.h"
#include "src/executor/brook.h"
#include "src/executor/server.h"
#include "src/executor/agent.h"
#include "src/executor/master.h"

namespace brook {

bool Initialize(int, char**);
std::string WorkerType();
void MasterWork();
void ServerWork();
void AgentWork();
void Finalize();

} // namespace brook

//----------------------------------------------------------------------
// The pre-defined main function
//----------------------------------------------------------------------

int main(int argc, char **argv) {
    // Parse command line flags, leaving argc unchanged, but rearrange
    // the arguments in argv so that the flags are all at the beginning.
    google::ParseCommandLineFlags(&argc, &argv, false);

    if (!brook::Initialize(argc, argv)) {
        LOG(ERROR) << "Initialization of Brook failed.";
        return -1;
    }

    LOG(INFO) << "I am a " << brook::WorkerType();

    if (brook::WorkerType() == "Master") {
        brook::MasterWork();
    } else if (brook::WorkerType() == "Server") {
        brook::ServerWork();
    } else {
        brook::AgentWork();
    }

    brook::Finalize();
    return 0;
}
