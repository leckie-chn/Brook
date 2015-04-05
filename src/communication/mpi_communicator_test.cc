// Copyright 2015 PKU-Cloud.
// Auhtor : Chao Ma (mctt90@gmail.com)
//
#include "src/communication/mpi_communicator.h"
#include "src/message/message.pb.h"
#include "src/message/partition.h"
#include "src/message/reader.h"

#include <mpi.h>
#include <string>
#include <iostream>

using namespace std;
using namespace brook;

typedef DoubleMessage Message;

const string double_test("TestDouble");
const uint64 max_features = 17;
const int num_server = 1;
const int num_agent = 1;
const int MAX_BUFFER_SIZE = 1 * 1024 * 1024; // 1 MB
const int MAX_QUEUE_SIZE = 10 * 1024 * 1024; // 10 MB

void NotifyFinished(MPICommunicator &comm) {
    Message msg;
    HeadMessage *ptr_hm = msg.mutable_head();
    ptr_hm->set_worker_id(1);
    ptr_hm->set_start_index(-1);
    string bytes;
    msg.SerializeToString(&bytes);
    comm.Send(bytes, 2);
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int m_rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &m_rank);

    if (m_rank == 1) { // Agent
        cout << "I'm agent" << endl;
        Partition p(max_features, num_server, num_agent);
        TextReader reader(p);
        reader.OpenFile(double_test);
        MPICommunicator communicator;
        communicator.Initialize("agent",
                                MAX_BUFFER_SIZE, 1,
                                MAX_QUEUE_SIZE,
                                MAX_QUEUE_SIZE);
        while (true) {
            Message msg;
            if (!reader.Read(msg)) break;
            HeadMessage *ptr_hm = msg.mutable_head();
            ptr_hm->set_worker_id(1);
            string bytes;
            msg.SerializeToString(&bytes);
            communicator.Send(bytes, p.NaiveShard(ptr_hm->start_index()));
        }
        NotifyFinished(communicator);
    }
    else if (m_rank == 2) { // server
        cout << "I'm server" << endl;
        MPICommunicator communicator;
        communicator.Initialize("server",
                                MAX_BUFFER_SIZE, 1,
                                MAX_QUEUE_SIZE,
                                MAX_QUEUE_SIZE);

        char buffer[MAX_BUFFER_SIZE];
        while (true) {
            int receive_bytes = communicator.Receive(buffer, MAX_BUFFER_SIZE);
            Message msg;
            CHECK(msg.ParseFromArray(buffer, receive_bytes));
            HeadMessage *ptr_hm = msg.mutable_head();
            if (ptr_hm->start_index() == -1) break;
            cout << "worker id: " << ptr_hm->worker_id() << endl;
            cout << "start index: " << ptr_hm->start_index() << endl;
            for (int i = 0 ; i < msg.list_size(); i++) {
                cout << msg.list(i) << endl;
            }
        }
        cout << "server finalzie. " << endl;
    }
    else { // master
        cout << "I'm master" << endl;
    }
  
    MPI_Finalize();

    return 0;
}
