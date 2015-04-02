// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#ifndef COMMUNICATION_MPI_COMMUNICATOR_H_
#define COMMUNICATION_MPI_COMMUNICATOR_H_

#include <mpi.h>

#include <iostream>
#include <string>
#include <vector>

#include "src/communication/communicator.h"
#include "src/message/partition.h"
#include "src/message/message.pb.h"
#include "src/util/common.h"
#include "src/util/logging.h"
#include "src/util/scoped_ptr.h"

using namespace std;

namespace brook {

//-----------------------------------------------------------
// Implement Communicator using MPI
//-----------------------------------------------------------
template <typename Message>
class MPISendRecv {
public:

    MPISendRecv(int buffer_size)
    : max_buffer_size_(buffer_size) {
        kAgentOutputTag_ = 1;
    }

    MPISendRecv(int buffer_size, Partition p) 
    : max_buffer_size_(buffer_size), partition_(p) { 
        kAgentOutputTag_ = 1;
    }
    
    virtual ~MPISendRecv() {} 

    virtual bool Initialize();
    virtual bool Finalize();

    virtual int Send(Message&);
    virtual int Recieve(Message&);

    virtual void AgentNotifyFinished(int, const vector<int>&);

    virtual void SendTo(Message&, int);
    virtual void SendToAll(Message&, const vector<int>&);

private:
    int kAgentOutputTag_;
    Partition partition_;
    scoped_array<char> AgentOutputBuffer;
    int max_buffer_size_;

};

template <typename Message>
bool MPISendRecv<Message>::Initialize() {
    try {
        AgentOutputBuffer.reset(new char[max_buffer_size_]);
    } catch (std::bad_alloc&) {
        LOG(ERROR) << "Can not allocation agent output buffer with size = "
                   << max_buffer_size_;
        return false;
    }
    return true;
}

template <typename Message>
bool MPISendRecv<Message>::Finalize() {
    return true;
}

template <typename Message>
int MPISendRecv<Message>::Send(Message& msg) {
    HeadMessage *ptr_hm = msg.mutable_head();
    int shard = partition_.NaiveShard(ptr_hm->start_index());
    SendTo(msg, shard);

    return 0;
}

template <typename Message>
void MPISendRecv<Message>::SendTo(Message& msg, int shard) {
    std::string bytes;
    msg.SerializeToString(&bytes);
    
    MPI_Send(const_cast<char*>(bytes.data()), 
             bytes.size(), 
             MPI_CHAR,
             shard, 
             kAgentOutputTag_, 
             MPI_COMM_WORLD);
}

template <typename Message>
void MPISendRecv<Message>::SendToAll(Message& msg, const vector<int>& server_list) {
    int len = server_list.size();
    for (int i = 0 ; i < len; i++) {
         SendTo(msg, server_list[i]);                                         
    }
}

template <typename Message>
void MPISendRecv<Message>::AgentNotifyFinished(int worker_id, const vector<int>& server_list) {
    // We set the start_index of HeadMessage to -1.
    // Notify that this agent has finished his work.
    Message msg;
    HeadMessage *ptr_hm = msg.mutable_head();
    ptr_hm->set_worker_id(1);
    ptr_hm->set_start_index(-1);
    // Tell every server.
    SendToAll(msg, server_list);
}

template <typename Message>
int MPISendRecv<Message>::Recieve(Message& msg) {

    MPI_Status status;
    int32 recieve_bytes = 0;

    MPI_Recv(AgentOutputBuffer.get(),
             max_buffer_size_,
             MPI_CHAR,
             MPI_ANY_SOURCE,
             kAgentOutputTag_, MPI_COMM_WORLD, &status);
    
    MPI_Get_count(&status, MPI_CHAR, &recieve_bytes);

    if (recieve_bytes >= max_buffer_size_) {
        LOG(FATAL) << "MPI_Recieving a proto message with size (at least) "
                   << recieve_bytes
                   << ", which >= max_buffer_size ("
                   << max_buffer_size_ << ")."
                   << "You can modify FLAGS_agent_output_size in "
                   << "configure file.";
    }

    CHECK(msg.ParseFromArray(AgentOutputBuffer.get(),
                             recieve_bytes));

    return 0;
}

} // namespace brook

#endif // COMMUNICATION_MPI_COMMUNICATOR_H_
