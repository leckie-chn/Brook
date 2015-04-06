// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/communication/signaling_queue.h"
#include "boost/thread.hpp"
#include "src/util/debug_print.h"
#include "src/system/mutex.h"

#include <string>

#include "gtest/gtest.h"

using std::string;
using namespace brook;

const int MAX_RECORD = 10000;
const int BUFFER_SIZE = 4;   // 4 KB
const int QUEUE_SIZE = 1024; // 1 MB
Mutex mutex;

TEST(SignalingQueueTest, AddRemove) {
    SignalingQueue queue(5, 1); // size: 5, num_of_producer:1
    char buff[10];
    queue.Add("111", 3);
    queue.Add("22", 2);
    EXPECT_EQ(0, queue.Add("xxxx", 4, false)); // non-blocking Add
    queue.Remove(buff, 3);
    EXPECT_EQ(string(buff, 3), string("111"));
    queue.Remove(buff, 2);
    EXPECT_EQ(string(buff, 2), string("22"));
    queue.Add("33333", 5);
    queue.Remove(buff, 5);
    EXPECT_EQ(string(buff, 5), string("33333"));
    EXPECT_EQ(0, queue.Remove(buff, 10, false)); // non-blocking remove
    EXPECT_EQ(queue.Add("666666", 6), -1);  // exceed buffer size
    queue.Add("55555", 5);
    EXPECT_EQ(queue.Remove(buff, 3), -1);
}

TEST(SignalingQueueTest, EmptyAndNoMoreAdd) {
    SignalingQueue queue(5, 2);
    char buff[10];
    EXPECT_EQ(queue.EmptyAndNoMoreAdd(), false);
    queue.Signal(1);
    queue.Signal(1);
    EXPECT_EQ(queue.EmptyAndNoMoreAdd(), false);
    queue.Signal(2);
    EXPECT_EQ(queue.EmptyAndNoMoreAdd(), true);
    EXPECT_EQ(queue.Remove(buff, 5), 0);
}

void AddDataToQueue(SignalingQueue *queue) {
    char send_buffer[BUFFER_SIZE];
    // Insert data to queue
    for (int i = 0 ; i < MAX_RECORD ; i++) {
        int* num = reinterpret_cast<int*>(send_buffer);
        *num = i;
        queue->Add(send_buffer, sizeof(int));
        MutexLocker locker(&mutex);
        DEBUG_PRINT("Add: ");
        DEBUG_PRINT_LINE(*num);
    }
}

void SendLoop(SignalingQueue *queue) {
    char recv_buffer[4];
    // remove data from queue
    while (true) {
        if (queue->EmptyAndNoMoreAdd()) break;
        int size = queue->Remove(recv_buffer, 4);
        int *num = reinterpret_cast<int*>(recv_buffer);
        MutexLocker locker(&mutex);
        DEBUG_PRINT("Remove: ");
        DEBUG_PRINT_LINE(*num);
    }
}

TEST(SignalingQueueTest, SendLoop) {
    // 32 MB, 1 producer
    SignalingQueue queue(QUEUE_SIZE);
    boost::thread *thread_send = new boost::thread(SendLoop, &queue);
    AddDataToQueue(&queue);
    // No more added
    queue.Signal(1);
    // Wait thread_send
    thread_send->join();
}

