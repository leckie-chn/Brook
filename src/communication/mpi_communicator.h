// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef COMMUNICATION_MPI_ASY_COMMUNICATOR_H_
#define COMMUNICATION_MPI_ASY_COMMUNICATOR_H_

#include <string>

#include "src/communication/communicator.h"
#include "src/communication/mpi_sendrecv.h"
#include "src/communication/signaling_queue.h"
#include "src/util/common.h"
#include "src/util/scoped_ptr.h"

#include "boost/thread.hpp"

namespace brook {

//---------------------------------------------------------------------- 
// Implement Communicator using MPICH
//----------------------------------------------------------------------
class MPICommunicator : public Communicator {
public:
    MPICommunicator() {}
    virtual ~MPICommunicator() {}

    virtual bool Initialize(std::string worker_type,
                            int output_size,      /*in bytes*/
                            int agent_queue_size  /*in bytes*/,
                            int server_queue_size /*in bytes*/);

    virtual bool Finalize();

    /* Send :
     * - send a message package to a specified server.
     * - actually write message into SignalingQueue.
     * Return:
     * > 0 : bytes send
     * - 1 : error
     * Note:
     * - The first 4 bytes is the receive_id (represented by uint32) and
     *   it will not be sent.
     */
    virtual int Send(void* src, int size);

    virtual int Send(const std::string &src);

    /* Receive : 
     * - receive a message package from any agent.
     * - actually read a message out from buffer
     * Return : 
     * > 0 : bytes received
     * - 1 : error
     */
    virtual int Receive(void* dest, int max_size);

    virtual int Receive(std::string *dest);

private:
    bool is_sender_;
    uint32 agent_queue_size_;
    uint32 server_queue_size_;
    int output_size_;
    scoped_array<char> output_buffer_;

    scoped_ptr<MPISendRecv> mpi_sendrecv_;
    scoped_ptr<SignalingQueue> receive_queue_;
    scoped_ptr<SignalingQueue> send_queue_;

    scoped_ptr<boost::thread> thread_send_;
    scoped_ptr<boost::thread> thread_receive_;


    bool InitSender();
    bool InitReceiver();
    bool FinalizeSender();
    bool FinalizeReceiver();

    static void SendLoop(MPICommunicator *pcom);
    static void ReceiveLoop(MPICommunicator *pcom);

    DISALLOW_COPY_AND_ASSIGN(MPICommunicator);

};

} // namespace brook

#endif // COMMUNICATION_MPI_ASY_COMMUNICATOR_H_
