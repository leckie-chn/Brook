// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/communication/mpi_sendrecv.h"

#include "src/util/debug_print.h"

namespace brook {

int MPISendRecv::Send(char* data_source, int len_data, int dest) {
    // MPI Send API
    MPI_Send(data_source, 
             len_data, 
             MPI_CHAR, 
             dest,
             kAgentOutputTag_, 
             MPI_COMM_WORLD);
    return len_data;
}

int MPISendRecv::Receive(char *buffer, int size_buffer) {
    MPI_Status status;
    int32 received_bytes = 0;

    // MPI Recv API
    MPI_Recv(buffer,
             size_buffer,
             MPI_CHAR,
             MPI_ANY_SOURCE,
             kAgentOutputTag_,
             MPI_COMM_WORLD,
             &status);

    MPI_Get_count(&status, MPI_CHAR, &received_bytes);

    if (received_bytes >= size_buffer) {
        LOG(FATAL) << "MPI_Receiving a proto message with size (at least)"
                   << received_bytes
                   << ", which >= FLAGS_max_agent_output_size ("
                   << size_buffer << ")."
                   << "You can modify this defined in configure file";
    }

    return received_bytes;
}

} // namespace
