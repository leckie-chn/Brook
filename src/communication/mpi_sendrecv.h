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

   virtual int Send(const char* data, int len_data, int dest);

   virtual int Receive(char * buffer, int size_buffer);

};

} // namespace brook

#endif // COMMUNICATION_MPI_SENDRECV_H_
