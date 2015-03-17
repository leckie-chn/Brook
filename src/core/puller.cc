// Copyright : 2014 PKU-Cloud.
// Auhtor: Chao Ma (mctt90@gmail.com)
//
#include "src/core/puller.h"
#include "src/core/flags.h"

#include <mpi.h>

namespace brook {

void Puller::Send() {
    // Loop until end of the file
    while (true) {
        if (!reader_.Read(&sm_)) {
            break;
        }
        std::string ssm;
        sm_.SerializeToString(&ssm);

        MPI_Send(const_cast<char*>(ssm.data()), ssm.size(), MPI_CHAR,
                 Shard(sm_.index()), kAgentSendTag, MPI_COMM_WORLD);
    }
    NotifyFinished();
}

int Puller::Shard(uint64 index) {
    return index / ChunkSize() + NumAgentWorkers();
}

void Puller::NotifyFinished() {
    SendMessage sm;
    sm.set_agent_worker(WorkerId());
    std::string ssm;
    sm.SerializeToString(&ssm);

    for (int s_id = NumAgentWorkers() ; s_id < NumWorkers() ; ++s_id) {
        MPI_Send(const_cast<char*>(ssm.data()), ssm.size(), MPI_CHAR,
                 s_id, kAgentSendTag, MPI_COMM_WORLD);
    }
}    

} // namespace brook
