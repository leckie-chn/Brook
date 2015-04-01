// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#ifndef COMMUNICATION_MPI_COMMUNICATOR_H_
#define COMMUNICATION_MPI_COMMUNICATOR_H_

#include <mpi.h>

#include "src/communication/communicator.h"

namespace brook {

//-----------------------------------------------------------
// Implement Communicator using MPI
//-----------------------------------------------------------
template <typename Message>
class MPICommunictor : public Communicator<Message> {
public:
    MPICommunictor() {}
    virtual ~MPICommunictor() {} 

    virtual bool Initialize() { return true; }
    virtual bool Finalize() { return true; }

    virtual int Send(Message&);
    virtual int Receive(Message&);

};

} // namespace brook

#endif // COMMUNICATION_MPI_COMMUNICATOR_H_
