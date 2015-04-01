// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#ifndef COMMUNICATION_MPI_COMMUNICATOR_H_
#define COMMUNICATION_MPI_COMMUNICATOR_H_

#include <mpi.h>

#include <string>

#include "src/communication/communicator.h"
#include "src/message/partition.h"
#include "src/util/common.h"
#include "src/util/logging.h"

namespace brook {

//-----------------------------------------------------------
// Implement Communicator using MPI
//-----------------------------------------------------------
template <typename Message>
class MPICommunictor : public Communicator<Message> {
public:
    MPICommunictor(int buffer_size) : max_buffer_size_(buffer_size) { 
        kAgentOutputTag_ = 1;
    }
    
    virtual ~MPICommunictor() {} 

    virtual bool Initialize();
    virtual bool Finalize();

    virtual int Send(Message&);
    virtual int Recieve(Message&);

private:
    int kAgentOutputTag_;
    Partition partition_;
    scoped_array<char> AgentOutputBuffer;
    int max_buffer_size_;

};

template <typename Message>
bool MPICommunictor<Message>::Initialize() {
    try {
        AgentOutputBuffer.reset(new char[buffer_size_]);
    } catch (std::bad_alloc&) {
        LOG(ERROR) << "Can not allocation agent output buffer with size = "
                   << buffer_size_;
        return false;
    }
    return true;
}

template <typename Message>
bool MPICommunictor<Message>::Finalize() {
    return true;
}

template <typename Message>
int MPICommunictor<Message>::Send(Message& msg) {
    std::string bytes;
    msg.SerializeToString(&bytes);

    MPI_Send(const_cast<char*>(bytes.data()), bytes.size(), MPI_CHAR,
             partition_.NaiveShard(msg.start_index()), kAgentOutputTag_,
             MPI_COMM_WORLD);
}

template <typename Message>
int MPICommunictor<Message>::Recieve(Message& msg) {
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
}

} // namespace brook

#endif // COMMUNICATION_MPI_COMMUNICATOR_H_
