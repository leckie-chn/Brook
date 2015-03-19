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

using brook::Row;
using brook::MessageSegment;
using brook::TimeStamp;
using brook::MessagePack;

TEST(SendMessage, basic) {
    Row row;
    row.add_value(0.12);
    row.add_value(1.12);
    MessagePack mp;
    for (int i = 0 ; i < 10 ; i++) {
        MessageSegment msg;
        msg.set_index(0 + i*10);
        for (int j = 0 ; j < 5 ; j++) {
            msg.mutabl
        }
        mp.add_msg(msg);
    }
    TimeStamp ts;
    ts.set_workerID(0);
    ts.set_time(11);
    mp.set_timestamp(ts);
}

