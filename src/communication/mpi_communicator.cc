// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//

#include "src/communication/mpi_communicator.h"
#include "src/util/stl-util.h"


namespace brook {

bool MPICommunicator::Initialize(std::string worker_type, 
                                 int output_size,
                                 int worker_id,
                                 int agent_queue_size, 
                                 int server_queue_size) 
{
    if (worker_type == "Server") {
        is_sender_ = false;
    } else is_sender_ = true;

    agent_queue_size_ = agent_queue_size;
    server_queue_size_ = server_queue_size;
    worker_id_ = worker_id;
    output_size_ = output_size;

    CHECK_LT(0, agent_queue_size_);
    CHECK_LT(0, server_queue_size_);
    CHECK_LT(0, output_size_);

    try {
        output_buffer_.reset(new char[output_size_]);
    } catch (std::bad_alloc&) {
        LOG(ERROR) << "Cannot allocate memory for output buffer";
        return false;
    }

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

int MPICommunicator::Send(void* src, int size, int  receive_id) {
    return send_buffer_->Add(reinterpret_cast<char*>(src), size, receive_id);
}

int MPICommunicator::Send(const string &src, int receive_id) {
    return send_buffer_->Add(src, receive_id);
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

bool MPICommunicator::FinalizeSender() {
    send_buffer_->Signal(worker_id_);
    thread_send_->join();

    return true;
}

bool MPICommunicator::FinalizeReceiver() {
    thread_receive_->join();
    receive_buffer_.reset(NULL);

    return true;
}

/*static*/
void MPICommunicator::SendLoop(MPICommunicator *comm) {
    // Send thread is working until task finished.
    while (true) {
        int shard = 0;
        // Get message from buffer
        int size = comm->send_buffer_->Remove(comm->output_buffer_.get(), 
                                              comm->output_size_, &shard);
        // Send message
        comm->mpi_sendrecv_->Send(comm->output_buffer_.get(), 
                                  size, shard);
    } 
}

/*static*/
void MPICommunicator::ReceiveLoop(MPICommunicator *comm) {
    // Recv thread is working until task finished.
    while (true) {
        // Recv message
        int size = comm->mpi_sendrecv_->Receive(comm->output_buffer_.get(), 
                                                comm->output_size_);
        
        // Insert message to receive_buffer_
        comm->receive_buffer_->Add(comm->output_buffer_.get(), size); 
    }
}


} // namespace brook
