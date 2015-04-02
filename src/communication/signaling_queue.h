// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef COMMUNICATION_SIGNALING_QUEUE_H_
#define COMMUNICATION_SIGNALING_QUEUE_H_

#include <queue>
#include <set>
#include <string>
#include <utility> // for pair<>

#include "src/base/common.h"
#include "src/system/condition_variable.h"
#include "src/system/mutex.h"
#include "src/message/message.pb.h"

namespace brook {

// SignalingQueue is a circle queue for using as a buffer in 
// the producer / consumer model. It supports one or more producer
// threads and one or more consumer threads. Producers invokes Add()
// to push data elements into the queue, and  consumers invokes
// Remove to pop data elements. Add() and Remove() use two condition
// variables to sychronize producers and comsumers. Each
// producer invokes Signal(producer_id) to claim that it is about to 
// finish, where producer_id is an integer uniquely identify a producer.
// This signaling mechanism prevents consumers from waiting
// after all producers have finished their generation.
//
// SignalingQueue is thread-safe.
//
template <typename Message>
class SignalingQueue {
public:
    SignalingQueue(int queue_size /*in bytes*/,
                   int num_producer = 1);

    ~SignalingQueue();

    // return : bytes added to queue
    // > 0 : size of message
    // = 0 : not enough space for this message (when is_blocking = false)
    // - 1 : error
    int Add(const char *src, int size, bool is_blocking = true);
    int Add(const std::string &src, bool is_blocking = true);

    // Remove a message from the queue
    // return: bytes removed from queue
    // > 0 : size of message
    // = 0 : queue of message
    //       invoke NoMoreAdd() to check if all producer have finished
    // - 1 : fail
    int Remove(char *dest, int max_size, bool is_blocking = true);
    int Remove(std::string *dest, bool is_blocking = true);

    // Signal that producer producer_id will no longer produce anything.
    // After all num_producer_ producers invoked Signal, a special message is
    // then inserted into the queue, so that the consumer can be notified to stop
    // working.
    void Signal(int producer_id);

    // Returns true if queue is empty and all num_producer producers have
    // Signaled their finish.
    bool EmptyAndNoMoreAdd() const;

private:

};


} // namespace brook

#endif // COMMUNICATION_SIGNALING_QUEUE_H_
