// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/message/partition.h"

#include "gtest/gtest.h"

using namespace std;
using namespace brook;

const uint64 feature_num = 17;
const uint32 server_num = 2;
const uint64 features[11] = {0, 1, 2, 5, 7, 9, 10, 11, 12, 15, 16};

TEST(PartitionTest, Partition) {
    Partition p(feature_num, num_server, num_agent);
    
}
