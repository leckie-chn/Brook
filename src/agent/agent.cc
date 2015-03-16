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

#include "src/core/flags.h"
#include "src/base/scoped_ptr.h"
#include "src/base/common.h"
#include "src/agent/reader.h"
#include "src/message/message.pb.h"

namespace brook {

using std::map;
using std::string;
using std::vector;

//-------------------------------------------------------
// Constants used by agent:
//-------------------------------------------------------

const int kAgentSendTag = 1;

//-------------------------------------------------------
// Initialization and Finalization of agent
//-------------------------------------------------------

bool AgentInitialize() {


    return true;
}

int Shard(uint64 index) {

    return 0;
}

void AgentWorkerNotifyFinished() {
    SendMessage sm;
    sm.set_agent_worker(WorkerId());
    string ssm;
    sm.SerializeToString(&ssm);

    // Send to all server workers.
    for (int s = NumAgentWorkers() ; s < NumWorkers() ; s++) {
        MPI_Send(const_cast<char*>(ssm.data()), ssm.size(), MPI_CHAR,
                 s, kAgentSendTag, MPI_COMM_WORLD);
    }
}

//-------------------------------------------------------
// Implementation of agent send work.
//-------------------------------------------------------
void SendWork() {
    // By default, we create a TextReader.
    // Maybe we will implemente the RecordReader in the future.
    scoped_ptr<Reader> reader(new TextReader());
    if (reader.get() == NULL) {
        LOG(FATAL) << "Creating reader error.";
    }
    reader->Open(SubDataCacheFile().c_str());

    SendMessage sm;
    while (true) {
        if (!reader->Read(&sm)) {
            break;
        }
        string ssm;
        sm.SerializeToString(&ssm);
        // Send message to server
        MPI_Send(const_cast<char*>(ssm.data()), ssm.size(), MPI_CHAR,
                 Shard(sm.index()), kAgentSendTag, MPI_COMM_WORLD);
    }
    // Important to tell server worekrs to terminate.
    AgentWorkerNotifyFinished();

    LOG(INFO) << "agent send work succssed.";
}



void AgentService() {
    
}    

void AgentFinalize() {

}

} // namespace brook
