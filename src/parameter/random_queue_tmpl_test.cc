// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/parameter/random_queue_tmpl.h"

#include "gtest/gtest.h"

using namespace std;
using namespace brook;

typedef RandomQueueTmpl<double> RandomQueue;

TEST(RandomQueueTest, PushAndPop) {
    RandomQueue rq;
    CHECK_EQ(rq.Size(), 0);
    rq.Push(1.0);
    rq.Push(2.0);
    EXPECT_EQ(rq.Size(), 2);
    double value = rq.Pop();
    EXPECT_EQ(value, 1.0);
    CHECK_EQ(rq.Size(), 1);
    value = rq.Pop();
    EXPECT_EQ(value, 2.0);
    EXPECT_EQ(rq.Size(), 0);
}

TEST(RandomQueueTest, GetAndSet) {
    RandomQueue rq;
    EXPECT_EQ(rq.Size(), 0);
    rq.Push(1.0);
    rq.Push(2.0);
    rq.Set(1, 2.5);
    double value = rq.Get(1);
    EXPECT_EQ(value, 2.5);
}
