// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#include "src/communication/mpi_communicator.h"
#include "src/message/message.pb.h"
#include "src/message/partition.h"
#include "src/message/reader.h"
#include "src/util/common.h"

#include <iostream>
#include <sys/types.h>
#include <unistd.h>

#include <mpi.h>

using namespace brook;
using namespace std;

typedef DoubleMessage Message;

const int MAX_BUFFER_SIZE = 32 * 1024 * 1024; // 32 MB
const string double_test("TestDouble");
const uint64 max_feature = 17;
const int num_server = 1;
const int num_agent = 1;

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);
 
    int m_rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &m_rank);

    if (m_rank ==  0) { // Agent
        Partition p(max_feature, num_server, num_agent);
        MPICommunicator<Message> sender(MAX_BUFFER_SIZE, p);
        TextReader reader(p);
        reader.OpenFile(double_test);
        while (true) {
            Message msg;
            if (!reader.Read(msg)) break;
            HeadMessage *ptr_hm = msg.mutable_head();
            ptr_hm->set_worker_id(1);
            sender.SendTo(msg, 1);
        }
    } else { // server
        MPICommunicator<Message> reciever(MAX_BUFFER_SIZE);
        reciever.Initialize();
        while(true) {
            Message msg;
            reciever.Recieve(msg);
            HeadMessage *ptr_hm = msg.mutable_head();
            cout << "worker id: " << ptr_hm->worker_id() << endl;
            cout << "start index: " << ptr_hm->start_index() << endl;
            for (int i = 0 ; i < msg.list_size(); i++) {
                cout << msg.list(i) << endl;
            }
        }
    }
}
