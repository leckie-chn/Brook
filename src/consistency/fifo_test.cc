// Copyright 2015 PKU-Cloud.
// Auhtor : Chao Ma (mctt90@gmail.com)
//
#include "src/consistency/fifo.h"

#include <string>
#include <fcntl.h>

#include "src/util/common.h"
#include "gtest/gtest.h"

using namespace std;
using brook::Fifo;

const string filename = "/tmp/test_fifo";
const int num = 12345;

TEST(FifoTest, ReadAndWrite) {
    int pid = fork();
    ASSERT_GE(pid, 0);
    if (pid > 0) { // Read
        Fifo fifo(filename);
        int read_num = fifo.ReadNum();
        EXPECT_EQ(read_num, num);
        cout << "Read process complete!";
    } else { // Write
        Fifo fifo(filename);
        sleep(3);
        fifo.WriteNum(num);
        cout << "Write process complete!";
    }
    
}
