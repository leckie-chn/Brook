// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
//
#include "src/message/message.pb.h"

#include <string>

#include "gtest/gtest.h"

using namespace std;
using brook::HeadMessage;
using brook::DoubleMessage;
using brook::VectorMessage;
using brook::Vector;

TEST(MessageTest, HeadMessage) {
    HeadMessage hm;
    hm.set_worker_id(1);
    hm.set_start_index(101);
    string str_hm;
    hm.SerializeToString(&str_hm);
    HeadMessage new_hm;
    new_hm.ParseFromString(str_hm);
    EXPECT_EQ(new_hm.worker_id(), 1);
    EXPECT_EQ(new_hm.start_index(), 101);
}

TEST(MessageTest, DoubleMessage) {
    DoubleMessage dm;
    HeadMessage *ptr_hm = dm.mutable_head();
    ptr_hm->set_worker_id(1);
    ptr_hm->set_start_index(101);
    dm.add_list(1.0);
    dm.add_list(1.1);
    string str_dm;
    dm.SerializeToString(&str_dm);
    DoubleMessage new_dm;
    new_dm.ParseFromString(str_dm);
    EXPECT_EQ(new_dm.mutable_head()->worker_id(), 1);
    EXPECT_EQ(new_dm.mutable_head()->start_index(), 101);
    EXPECT_EQ(new_dm.list(0), 1.0);
    EXPECT_EQ(new_dm.list(1), 1.1);
}

TEST(MessageTest, VectorMessage) {
    VectorMessage vm;
    HeadMessage *ptr_hm = vm.mutable_head();
    ptr_hm->set_worker_id(1);
    ptr_hm->set_start_index(101);
    for (int i = 0 ; i < 3 ; i++) {
        Vector *ptr_vec = vm.add_list();
        ptr_vec->add_value(1.0);
        ptr_vec->add_value(1.2);
        ptr_vec->add_value(1.3);
    }
}
