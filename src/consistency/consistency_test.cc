// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/consistency/consistency.h"
#include "src/util/common.h"

#include "gtest/gtest.h"

#include <string>

using namespace std;
using namespace brook;

const string filename_base = "/tmp/test_fifo";
const int iteration_num = 10;

void agent_do_something() {
    sleep(1);
}

void user_do_something() {
    sleep(1);
}

TEST(AgentConsistencyTest, BSP) {
    string reader = filename_base + "reader";
    string writer = filename_base + "writer";
    int pid = fork();
    ASSERT_GE(pid, 0);
    if (pid > 0) { // Agent
        int reader_fp = OpenReadFifo(reader);
        int writer_fp = OpenWriteFifo(writer);
        AgentConsistency agent(reader_fp, writer_fp);
        for (int i = 0 ; i < iteration_num ; i++) {
            agent.WaitSignal();
            agent_do_something();
            cout << "agent: " << i << endl;
            agent.IncreaseSignal();
        }
    } else { // User
        int writer_fp = OpenWriteFifo(reader);
        int reader_fp = OpenReadFifo(writer);
        BSP user(reader_fp, writer_fp);
        for (int i = 0 ; i < iteration_num ; i++) {
            user_do_something();
            cout << "user: " << i << endl;
            user.IncreaseSignal();
            user.WaitSignal();
        }
    }
}
