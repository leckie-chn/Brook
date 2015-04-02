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
    SignalingQueue(int queue_size /*len*/,
                   int num_producer = 1);

    ~SignalingQueue();

    void Add(const )
};


} // namespace brook

#endif // COMMUNICATION_SIGNALING_QUEUE_H_
