// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//

#include "src/parameter/version_buffer_tmpl.h"
#include "src/parameter/dense_vector_tmpl.h"

#include <iostream>

#include "gtest/gtest.h"

using namespace std;
using namespace brook;

typedef VersionBufferTmpl<double> VersionBuffer;
typedef DenseVectorTmpl<double> DenseVector;

const int feature_num = 2;
const int bit_size = 2;
const int num_agent = 2;

const int worker_1 = 0;
const int worker_2 = 1;

TEST(VersionBufferTest, SetAndGet) {
    // feature_num = 3, bit_size = 3, num_agent = 3;
    VersionBuffer buffer(feature_num, bit_size, num_agent);   
    buffer.Set(0, 0, 0.1);
    buffer.Set(1, 0, 0.2);

    double value = buffer.Get(0, 0);
    EXPECT_EQ(value, 0.1);
    value = buffer.Get(1, 0);
    EXPECT_EQ(value, 0.2);
}

TEST(VersionBufferTest, InsertUpdate) {
    VersionBuffer buffer(feature_num, bit_size, num_agent);
    buffer.InsertUpdate(worker_1, 0, 1.0); // iter 0
    buffer.InsertUpdate(worker_2, 0, 1.0); // iter 0
    buffer.InsertUpdate(worker_1, 1, 2.0); // iter 0
    // suppose we receive the final message of worker_1.
    buffer.AddFinishedCount(buffer.GetAgentTimestamp()[worker_1]);
    buffer.AddAgentTimestamp(worker_1);
    EXPECT_EQ(buffer.CurrentIterationFinished(), false);
    buffer.InsertUpdate(worker_1, 0, 1.0); // iter 1
    EXPECT_EQ((*buffer.GetBuffer())[worker_1].Size(), 2);
    buffer.InsertUpdate(worker_2, 1, 2.0); // iter 0
    // suppose we receive the final meesage of worker_2.
    buffer.AddFinishedCount(buffer.GetAgentTimestamp()[worker_2]);
    buffer.AddAgentTimestamp(worker_2); 
    EXPECT_EQ(buffer.CurrentIterationFinished(), true);
    DenseVector *vec = buffer.GetOldestUpdates();
    EXPECT_EQ(vec->size(), 2);
    EXPECT_EQ((*vec)[0], 2.0);
    EXPECT_EQ((*vec)[1], 4.0);
    EXPECT_EQ(buffer.CurrentIterationFinished(), false);
    buffer.InsertUpdate(worker_2, 0, 3.0); // iter 1
    buffer.InsertUpdate(worker_1, 1, 5.0); // iter 1
    // suppose we receive the final message of worker_1
    buffer.AddFinishedCount(buffer.GetAgentTimestamp()[worker_1]);
    buffer.AddAgentTimestamp(worker_1);
    EXPECT_EQ(buffer.CurrentIterationFinished(), false);
    buffer.InsertUpdate(worker_2, 1, 5.0); // iter 1
    // suppose we receive the final message of worker_2
    buffer.AddFinishedCount(buffer.GetAgentTimestamp()[worker_2]);
    buffer.AddAgentTimestamp(worker_2);
    EXPECT_EQ(buffer.CurrentIterationFinished(), true);
    EXPECT_EQ(buffer.GetAgentTimestamp()[worker_1], 2.0);
    EXPECT_EQ(buffer.GetAgentTimestamp()[worker_2], 2.0);
    vec = buffer.GetOldestUpdates();
    EXPECT_EQ((*vec).size(), 2);
    EXPECT_EQ((*vec)[0], 4.0);
    EXPECT_EQ((*vec)[1], 10.0);
}
