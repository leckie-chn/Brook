// Copyright : 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include <mpi.h>
#include <stdio.h>

#include <map>
#include <new>
#include <set>
#include <string>
#include <vector>

#include "boost/filesystem.hpp"

#include "src/agent/agent.h"
#include "src/agent/flags.h"
#include "src/agent/reader.h"
#include "src/base/common.h"
#include "src/base/logging.h"
#include "src/base/scoped_ptr.h"
#include "src/base/filepattern.h"
#include "src/base/stl-util.h"
#include "gflags/gflags.h"
#include "src/hash/simple_hash.h"
#include "google/protobuf/message.h"
#include "src/strutil/join_strings.h"
#include "src/strutil/stringprintf.h"


namespace brook {

using std::map;
using std::string;
using std::vector;

//-------------------------------------------------------------------
// Brook context, using poor guy's singleton.
//-------------------------------------------------------------------

scoped_array<char>& GetAgentOutputSendBuffer() {
    static scoped_array<char> agent_output_send_buffer;
    return agent_output_send_buffer;
}

//-------------------------------------------------------------------
// Initialization and Finalization of agent
//-------------------------------------------------------------------
bool Agent_Initialize(int argc, char **argv) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    // ValidateCommandLineFlags
    if (!ValidateCommandLineFlags()) {
        LOG(ERROR) << "Failed validating command line flags.";
        return false;
    }

    // Redirect log messages to disk files from terminal. Note that
    // LogFilebase() is valid only after ValidateCommandLineFlags.
    string filename_prefix = LogFilebase();
    InitializeLogger(StringPrintf("%s.INFO", filename_prefix.c_str()),
                     StringPrintf("%s.WARN", filename_prefix.c_str()),
                     StringPrintf("%s.ERROR", filename_prefix.c_str()));

    // Create agent output sending buffer for agent worker.
    try {
        GetAgentOutputSendBuffer().reset(new char[AgentOutputBufferSize()]);
    } catch(std::bad_alloc) {
        LOG(ERROR) << "Cannot allocation agent output send buffer with size = "
                   << AgentOutputBufferSize();
        return false;
    }

    return true;
}

//-------------------------------------------------------------------
// Finalization of agent
//-------------------------------------------------------------------
void Agent_Finalize() {
    
    LOG(INFO) << "Agent service finalized.";
}

// The count of row data records.
uint64 g_count_record = 0;

void SendWork() {
    // Clear counters.
    g_count_record = 0;

    // scoped_ptr<Reader> reader();
}

//-------------------------------------------------------------------
// Agent service
//-------------------------------------------------------------------
void Agent_Service() {
    LOG(INFO) << "Start agent service";


}

} // namespace brook
