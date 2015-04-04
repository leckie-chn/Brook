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

bool MPICommunicator::InitSender() {
    try {
        send_buffer_.reset(new SignalingQueue(agent_queue_size_));
        thread_send_.reset(new boost::thread(SendLoop, this));
    } catch(std::bad_alloc&) {
        LOG(ERROR) << "Cannot allocate memory for sender";
        return false;
    }

    return true;
}

bool MPICommunicator::InitReceiver() {
    try {
        receive_buffer_.reset(new SignalingQueue(server_queue_size_));
        thread_receive_.reset(new boost::thread(ReceiveLoop, this));
    } catch(std::bad_alloc&) {
        LOG(ERROR) << "Cannot allocate memory for receiver";
        return false;
    }

    return true;
}

int MPICommunicator::Send(void* src, int size) {
    return send_buffer_->Add(reinterpret_cast<char*>(src), size);
}

int MPICommunicator::Send(const string &src) {
    return send_buffer_->Add(src);
}

int MPICommunicator::Receive(void *dest, int max_size) {
    return receive_buffer_->Remove(reinterpret_cast<char*>(dest), max_size);
}

int MPICommunicator::Receive(string *dest) {
    return receive_buffer_->Remove(dest);
}

bool MPICommunicator::Finalize() {
    if (is_sender_) {
        return FinalizeSender();
    } else {
        return FinalizeReceiver();
    }
}

/*static*/
void MPICommunicator::SendLoop(MPICommunicator *comm) {
    
}

/*static*/
void MPICommunicator::ReceiveLoop(MPICommunicator *comm) {

}


} // namespace brook
