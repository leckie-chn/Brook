// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#ifndef COMMUNICATION_MPI_COMMUNICATOR_H_
#define COMMUNICATION_MPI_COMMUNICATOR_H_

#include <mpi.h>

#include <string>

#include "src/communication/communicator.h"
#include "src/message/partition.h"

namespace brook {

//-----------------------------------------------------------
// Implement Communicator using MPI
//-----------------------------------------------------------
template <typename Message>
class MPICommunictor : public Communicator<Message> {
public:
    MPICommunictor(int buffer_size) : buffer_size_(buffer_size) { 
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
    char *recieve_buffer_;
    int buffer_size_;

};

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
    MPI_Recv()
}

} // namespace brook

#endif // COMMUNICATION_MPI_COMMUNICATOR_H_
