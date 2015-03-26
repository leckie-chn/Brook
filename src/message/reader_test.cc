// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/message/reader.h"
#include "src/message/message.pb.h"

#include <string>
#include <iostream>

#include "gtest/gtest.h"

using namespace std;
using brook::TextReader;
using brook::DoubleMessage;
using brook::HeadMessage;

const string double_test("TestDouble");

TEST(TextReaderTest, Read) {
    TextReader reader;
    reader.OpenFile(double_test);
    while (true) {
        DoubleMessage msg;
        bool flag = reader.Read(msg);
        if (msg.has_head()) {
            HeadMessage *ptr_hm = msg.mutable_head();
            //cout << "worker id: " << ptr_hm->worker_id() << endl;
            cout << "start index: " << ptr_hm->start_index() << endl;
            for (int i = 0 ; i < msg.list_size() ; i++) {
                cout << msg.list(i) << endl;
            }
        }
        if (!flag) break;
    }
}