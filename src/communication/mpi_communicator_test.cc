// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#include "src/communication/mpi_communicator.h"
#include "src/message/message.pb.h"
#include "src/message/partition.h"
#include "src/message/reader.h"
#include "gtest/gtest.h"

#include <mpi.h>

using namespace brook;
using namespace std;

typedef DoubleMessage Message;

const int MAX_BUFFER_SIZE = 32 * 1024 * 1024; // 32 MB
const string double_test("TestDouble");
const uint64 max_feature = 16;
const int num_server = 1;
const int num_agent = 1;

TEST(MPI_COMMUNICATION_TEST, SendAndRecv) {
    int pid;
    pid = fork();
    ASSERT_LE(0, pid);
    if (pid > 0) { // Agent
        Partition p(max_feature, num_server, num_agent);
        MPICommunicator<Message> sender(MAX_BUFFER_SIZE, p);
        TextReader reader(p);
        reader.OpenFile(double_test);
        while (true) {
            
        }
        
    } else { // server
            
    }
}
