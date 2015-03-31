// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/consistency/consistency.h"
#include "src/consistency/fifo.h"
#include "gtest/gtest.h"

#include <string>

using namespace std;
using namespace brook;

const string filename_base = "/tmp/test_fifo";
const int worker_id = 8;

TEST(AgentConsistencyTest, WaitSignal) {
    string reader = filename_base + worker_id + "reader";
    string writer = filename_base + worker_id + "writer";
    AgentConsistency(reader, writer);
}
