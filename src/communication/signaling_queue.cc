// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//

#include "src/communication/signaling_queue.h"

#include <cstring>

namespace brook {

using std::string;

SignalingQueue::SignalingQueue(int queue_size, int num_producers) {
    CHECK_LT(0, queue_size);
    try {
        queue_ = new char[queue_size];
    } catch(const std::bad_alloc&) {
        LOG(FATAL) << "Not enough memory for message buffer.";
    }
    memset(queue_, '\0', queue_size);
    
    queue_size_    = queue_size;
    free_size_     = queue_size;
    write_pointer_ = 0;
    num_producers_ = num_producers;
}

SignalingQueue::~SignalingQueue() {
    MutexLocker locker(&mutex_);
    if (NULL != queue_) {
        delete [] queue_;
        queue_ = NULL;
    }
}

int SignalingQueue::Add(const char *src, int size, bool is_blocking) {
    // check if message too long to fit in the queue.
    if (size > queue_size_) {
        LOG(ERROR) << "Message is larger than the queue.";
        return -1;
    }

    if (size <= 0) {
        LOG(ERROR) << "Message size (" << size << ") is negative or zero.";
        return -1;
    }

    MutexLocker locker(&mutex_); // lock
    if (finished_producers_.size() >= num_producers_) {
        LOG(ERROR) << "Can't add to buffer when flag_no_more is set.";
        return -1;
    }

    while (size > free_size_) {
        if (!is_blocking) {
            return 0;
        }
        cond_not_full_.Wait(&mutex_);
    }

    // write data into buffer:
    // if there is enough space on tail of buffer, just append data
    // else, write till the end of buffer and return th head of buffer.
    message_positions_.push(std::make_pair(write_pointer_, size));
    free_size_ -= size;
    if (write_pointer_ + size <= queue_size_) {
        memcpy(&queue_[write_pointer_], src, size);
        write_pointer_ += size;
        if (write_pointer_ == queue_size_) {
            write_pointer_ = 0;
        }
    } else {
        int size_partial = queue_size_ - write_pointer_;
        memcpy(&queue_[write_pointer_], src, size_partial);
        memcpy(queue_, &src[size_partial], size - size_partial);
        write_pointer_ = size - size_partial;
    }

    // not empty signal
    cond_not_empty_.Signal();

    return size;
}

int SignalingQueue::Add(const string &src, bool is_blocking) {
    return Add(src.data(), src.size(), is_blocking);
}

int SignalingQueue::Remove(char *dest, int max_size, bool is_blocking) {
    int retVal;

    MutexLocker locker(&mutex_);
    while (message_positions_.empty()) {
        if (!is_blocking) {
            return 0;
        }
        if (finished_producers_.size() >= num_producers_) {
            return 0;
        }
        cond_not_empty_.Wait(&mutex_);
    }
    MessagePosition & pos = message_positions_.front();
    // check if message too long.
    if (pos.second > max_size) {
        LOG(ERROR) << "Message size exceeds limit, information lost.";
        retVal = -1;
    } else {
        // read from buffer:
        // if this message stores in consecutive memory, just read
        // else, read from buffer tail then return to head
        if (pos.first + pos.second <= queue_size_) {
            memcpy(dest, &queue_[pos.first], pos.second);
        } else {
            int size_partial = queue_size_ - pos.first;
            memcpy(dest, &queue_[pos.first], size_partial);
            memcpy(&dest[size_partial], queue_, pos.second - size_partial);
        }
        retVal = pos.second;
    }
    free_size_ += pos.second;
    message_positions_.pop();

    cond_not_full_.Signal();

    return retVal;
}

int SignalingQueue::Remove(string *dest, bool is_blocking) {
    int ret_val;

    MutexLocker locker(&mutex_);
    while (message_positions_.empty()) {
        if (!is_blocking) {
            return 0;
        }
        if (finished_producers_.size() >= num_producers_) {
            return 0;
        }
        cond_not_empty_.Wait(&mutex_);
    }

    MessagePosition & pos = message_positions_.front();
    // read from buffer:
    // if this message stores in consecutive memory, just read
    // else, read from buffer tail then return head
    if (pos.first + pos.second <= queue_size_) {
        dest->assign(&queue_[pos.first], pos.second);
    } else {
        int size_partial = queue_size_ - pos.first;
        dest->assign(&queue_[pos.first], size_partial);
        dest->assign(queue_, pos.second - size_partial);
    }
    ret_val = pos.second;
    free_size_ += pos.second;
    message_positions_.pop();

    cond_not_full_.Signal();

    return ret_val;
}

void SignalingQueue::Signal(int producer_id) {
    MutexLocker locker(&mutex_);
    finished_producers_.insert(producer_id);

    // if all Producers have finished, consumer should be waken up to 
    // get this signal.
    if (finished_producers_.size() >= num_producers_) {
        cond_not_empty_.Broadcast();
    }
}

bool SignalingQueue::EmptyAndNoMoreAdd() const {
    MutexLocker locker(&mutex_);
    return message_positions_.size() == 0 &&
           finished_producers_.size() >= num_producers_;
}


} // namespace brook
