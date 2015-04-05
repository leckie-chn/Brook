// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/communication/mpi_sendrecv.h"
#include "src/message/message.pb.h"
#include "src/message/partition.h"
#include "src/message/reader.h"

#include "gtest/gtest.h"

#include <mpi.h>
#include <string>
#include <iostream>

using namespace std;
using namespace brook;

typedef DoubleMessage Message;

const string double_test("TestDouble");
const uint64 max_feature = 17;
const int num_server = 1;
const int num_agent = 1;
const int MAX_BUFFER_SIZE = 32 * 1024 * 1024; // 32 MB

char buffer[MAX_BUFFER_SIZE];

void NotifyFinished(MPISendRecv& sender) {
    Message msg;
    HeadMessage *ptr_msg = msg.mutable_head();
    ptr_msg->set_worker_id(1);
    ptr_msg->set_start_index(-1);
    string bytes;
    msg.SerializeToString(&bytes);
    sender.Send(const_cast<char*>(bytes.data()), bytes.size(), 2);
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int m_rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &m_rank);

    if (m_rank == 1) { // Agent
        cout << "I'm agent" << endl;
        Partition p(max_feature, num_server, num_agent);
        TextReader reader(p);
        reader.OpenFile(double_test);
        MPISendRecv sender;
        while (true) {
            Message msg;
            if (!reader.Read(msg)) break;
            HeadMessage *ptr_hm = msg.mutable_head();
            ptr_hm->set_worker_id(1);
            string bytes;
            msg.SerializeToString(&bytes);
            sender.Send(const_cast<char*>(bytes.data()), bytes.size(), p.NaiveShard(ptr_hm->start_index()));
        }
        NotifyFinished(sender);
    } 
    else if (m_rank == 2) { // server
        cout << "I'm server" << endl;
        MPISendRecv recver;
        while (true) {
            int recv_bytes = recver.Receive(buffer, MAX_BUFFER_SIZE);
            Message msg;
            CHECK(msg.ParseFromArray(buffer, recv_bytes));
            HeadMessage *ptr_hm = msg.mutable_head();
            if (ptr_hm->start_index() == -1) break;
            cout << "worker id: " << ptr_hm->worker_id() << endl;
            cout << "start index: " << ptr_hm->start_index() << endl;
            for (int i = 0 ; i < msg.list_size() ; i++) {
                cout << msg.list(i) << endl;
            }
        }
        cout << "server finalize." << endl;
    } 
    else { // master
        cout << "I'm master" << endl;                 
    }

    MPI_Finalize();

    return 0;
}
