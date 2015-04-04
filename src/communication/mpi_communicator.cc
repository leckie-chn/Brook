// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//

#include "src/communication/mpi_communicator.h"

namespace brook {

bool MPICommunicator::Initialize(std::string worker_type, 
                                 int agent_queue_size, 
                                 int server_queue_size) 
{
    if (worker_type == "Server") {
        is_sender_ = false;
    } else is_sender_ = true;

    agent_queue_size_ = agent_queue_size;
    server_queue_size_ = server_queue_size;

    CHECK_LT(0, agent_queue_size_);
    CHECK_LT(0, server_queue_size_);

    if (is_sender_) {
        return InitSender();
    } else {
        return InitReceiver();
    }
}

} // namespace brook
