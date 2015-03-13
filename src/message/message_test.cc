// Copyright : 2015 pku-Cloud.
// Athour: Chao Ma (mctt90@gmail.com)
//
#include "src/message/message.pb.h"

#include <iostream>
#include <vector>
#include <string>

#include "src/base/common.h"
#include "gtest/gtest.h"

using namespace std;

using brook::ValueList;
using brook::SendMessage;

TEST(SendMessage, basic) {
    vector<double> vec_list;
    vec_list.push_back(1.1);
    vec_list.push_back(0.5);
    SendMessage sm;
    sm.mutable_list()->Clear();
    uint64 index = 5;
    sm.set_index(index);
    for (int i = 0 ; i < vec_list.size() ; i++) {
        sm.mutable_list()->add_value(vec_list[i]);
    }
    string output_buffer;
    sm.SerializeToString(&output_buffer);
    SendMessage recv_message;
    recv_message.ParseFromString(output_buffer);
    EXPECT_EQ(recv_message.index(), 5);
    EXPECT_EQ(recv_message.list().value_size(), 2);
    EXPECT_EQ(recv_message.list().value(0), 1.1);
    EXPECT_EQ(recv_message.list().value(1), 0.5);
}

