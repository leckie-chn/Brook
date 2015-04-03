// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef COMMUNICATION_MPI_ASY_COMMUNICATOR_H_
#define COMMUNICATION_MPI_ASY_COMMUNICATOR_H_

#include "src/communication/communicator.h"
#include "src/communication/mpi_sendrecv.h"
#include "src/communication/signaling_queue.h"
#include "src/util/common.h"

namespace brook {

class MPICommunicator : public Communicator {
public:
    MPICommunicator() {}
    virtual ~MPICommunicator() {}

    virtual 

private:
    bool is_sender_;
    uint32 agent_queue_size_;
    uint32 server_queue_size_;
    
    scoped_ptr<MPISendRecv> mpi_sendrecv_;
    scoped_ptr<SignalingQueue> receive_buffer_;
    scoped_ptr<SignalingQueue> send_buffer_;

    scoped_ptr<boost::thread> thread_send_;
    scoped_ptr<boost::thread> thread_receive_;

    static void SendLoop(SocketCommunicator *pcom);
    static void ReceiveLoop(SocketCommunicator *pcom);

    DISALLOW_COPY_AND_ASSIGN(SocketCommunicator);

};

} // namespace brook

#endif // COMMUNICATION_MPI_ASY_COMMUNICATOR_H_
