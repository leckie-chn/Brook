// Copyright 2015 PKU-Cloud.
// Auhtor : Chao Ma (mctt90@gmail.com)
//
#include "src/consistency/fifo.h"

#include <string>
#include <fcntl.h>

#include "src/util/common.h"
#include "gtest/gtest.h"

using namespace std;
using namespace brook;

const string filename = "/tmp/test_fifo";
const int num = 2345;

TEST(FifoTest, ReadAndWrite) {
    int pid = fork();
    ASSERT_GE(pid, 0);
    if (pid > 0) { // Read
        int fp = OpenReadFifo(filename);
        int read_num = FifoReadNum(fp);
        EXPECT_EQ(read_num, num);
        cout << "Read process complete!";
    } else { // Write
        int fp = OpenWriteFifo(filename);
        sleep(3);
        WriteNum(num, fp);
        cout << "Write process complete!";
    } 
}
