// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/message/reader.h"
#include "src/message/message.pb.h"
#include "src/message/partition.h"

#include <string>
#include <iostream>

#include "gtest/gtest.h"

using namespace std;
using namespace brook;

const string double_test("TestDouble");
const uint64 max_feature = 17;
const int num_server = 1;

TEST(TextReaderTest, Read) {
    AveragePartition p(max_feature, num_server);
    TextReader reader(&p);
    reader.OpenFile(double_test);
    while (true) {
        DoubleMessage msg;
        if (!reader.Read(msg)) break;
        HeadMessage *ptr_hm = msg.mutable_head();
        ptr_hm->set_worker_id(1);
        cout << "worker id: " << ptr_hm->worker_id() << endl;
        cout << "start index: " << ptr_hm->start_index() << endl;
        for (int i = 0 ; i < msg.list_size() ; i++) {
            cout << msg.list(i) << endl;
        }
    }
}
