// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/message/partition.h"

#include <iostream>

#include "gtest/gtest.h"

using namespace std;
using namespace brook;

#define LEN 12

const uint64 feature_num = 18;
const uint32 server_num = 4;
const uint64 features[LEN] = {0, 1, 2, 5, 7, 9, 10, 11, 12, 15, 16, 17};

TEST(PartitionTest, Partition) {
    AveragePartition p(feature_num, server_num);
    vector<int> res(LEN);
    for (int i = 0 ; i < LEN ; i++) {
        res[i] = p.Shard(features[i]);
        cout << res[i] << endl;
    }
}
