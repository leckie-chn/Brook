// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef COMMUNICATION_MPI_SENDRECV_H_
#define COMMUNICATION_MPI_SENDRECV_H_

#include <mpi.h>

#include <string>
#include <vector>

#include "src/util/common.h"
#include "src/util/logging.h"
#include "src/util/scoped_ptr.h"

using namespace std;

namespace brook {

// MPISendRecv is a simple wrapper around MPI.

class MPISendRecv {
public:

    MPISendRecv() { kAgentOutputTag_ = 1; }
 
    // Note :
    // The first 4 bytes is the receive_id (represented by uint32) and
    // it will not be sent.
    virtual int Send(char *data_source, int len_data);

    virtual int Receive(char *buffer, int size_buffer);

private:
    int kAgentOutputTag_;

};

} // namespace brook

#endif // COMMUNICATION_MPI_SENDRECV_H_
