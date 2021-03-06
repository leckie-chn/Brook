// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/communication/mpi_communicator.h"
#include "src/util/stl-util.h"

#include "src/util/debug_print.h"

namespace brook {

bool MPICommunicator::Initialize(std::string worker_type, 
                                 int output_size,
                                 int agent_queue_size, 
                                 int server_queue_size) 
{
    if (worker_type != "Server" && worker_type != "Agent") {
        LOG(ERROR) << "worker_type neither be Server nor Agent.";
        return false;
    }
    if (worker_type == "Server") {
        is_sender_ = false;
    } else is_sender_ = true;

    agent_queue_size_ = agent_queue_size;
    server_queue_size_ = server_queue_size;
    output_size_ = output_size;

    CHECK_LT(0, agent_queue_size_);
    CHECK_LT(0, server_queue_size_);
    CHECK_LT(0, output_size_);

    mpi_sendrecv_.reset(new MPISendRecv());

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
        send_queue_.reset(new SignalingQueue(agent_queue_size_));
        thread_send_.reset(new boost::thread(SendLoop, this));
    } catch(std::bad_alloc&) {
        LOG(ERROR) << "Cannot allocate memory for sender";
        return false;
    }

    return true;
}

bool MPICommunicator::InitReceiver() {
    try {
        receive_queue_.reset(new SignalingQueue(server_queue_size_));
        thread_receive_.reset(new boost::thread(ReceiveLoop, this));
    } catch(std::bad_alloc&) {
        LOG(ERROR) << "Cannot allocate memory for receiver";
        return false;
    }
    return true;
}

int MPICommunicator::Send(void* src, int size) {
    return send_queue_->Add(reinterpret_cast<char*>(src), size);
}

int MPICommunicator::Send(const string &src) {
    return send_queue_->Add(src);
}

int MPICommunicator::Receive(void *dest, int max_size) {
    return receive_queue_->Remove(reinterpret_cast<char*>(dest), max_size);
}

int MPICommunicator::Receive(string *dest) {
    return receive_queue_->Remove(dest);
}

bool MPICommunicator::Finalize() {
    if (is_sender_) {
        return FinalizeSender();
    } else {
        return FinalizeReceiver();
    }
}

bool MPICommunicator::FinalizeSender() {
    // Signal consumer finished.
    // Because MPICommunicator using 1 producer - 1 consumer model.
    // so this invocation will finish the send thread.
    send_queue_->Signal(1);
    // Wait thread_send_ finish.
    thread_send_->join();

    return true;
}

bool MPICommunicator::FinalizeReceiver() {
    // Signal producer finished.
    receive_queue_->Signal(1);
    // Wait thread_receive_ finish.
    thread_receive_->join();

    return true;
}

/*static*/
void MPICommunicator::SendLoop(MPICommunicator *comm) {
    // Send thread is working until task finished.
    while (true) {
        if (comm->send_queue_->EmptyAndNoMoreAdd()) {
            break;
        }
        // Get message from buffer
        int size = comm->send_queue_->Remove(comm->output_buffer_.get(), 
                                              comm->output_size_);
        // Send message
        comm->mpi_sendrecv_->Send(comm->output_buffer_.get(), size);
    } 
}

/*static*/
void MPICommunicator::ReceiveLoop(MPICommunicator *comm) {
    // Recv thread is working until task finished.
    while (true) {
        if (comm->receive_queue_->EmptyAndNoMoreAdd()) {
            break;
        }
        // Recv message
        int size = comm->mpi_sendrecv_->Receive(comm->output_buffer_.get(), 
                                                comm->output_size_);
        // Insert message to receive_buffer_
        comm->receive_queue_->Add(comm->output_buffer_.get(), size); 
    }
}


} // namespace brook
