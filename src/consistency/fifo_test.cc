// Copyright 2015 PKU-Cloud.
// Auhtor : Chao Ma (mctt90@gmail.com)
//
#include "src/consistency/fifo.h"

#include <string>
#include <fcntl.h>

#include "gtest/gtest.h"

using namespace std;
using brook::Fifo;

const string filename = "/tmp/test_fifo";

TEST(FifoTest, CreateAndDestroy) {
    Fifo fifo(filename, O_RDWR);
}
