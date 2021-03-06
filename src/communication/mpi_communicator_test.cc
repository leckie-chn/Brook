// Copyright 2015 PKU-Cloud.
// Auhtor : Chao Ma (mctt90@gmail.com)
//
#include "src/communication/mpi_communicator.h"
#include "src/message/message.pb.h"
#include "src/message/partition.h"
#include "src/message/reader.h"
#include "src/util/debug_print.h"

#include <mpi.h>
#include <string>
#include <iostream>

using namespace std;
using namespace brook;

typedef DoubleMessage Message;

const string double_test("TestDouble");
const uint64 max_features = 17;
const int num_server = 2;
const int num_agent = 1;
const int MAX_BUFFER_SIZE = 1 * 1024 * 1024; // 1 MB
const int MAX_QUEUE_SIZE = 10 * 1024 * 1024; // 10 MB
const uint32 receive_id = 2;


void NotifyFinished(MPICommunicator &sender, char* send_buffer) {
    Message msg;
    HeadMessage *ptr_hm = msg.mutable_head();
    ptr_hm->set_worker_id(1);
    ptr_hm->set_start_index(-1);
    string bytes;
    msg.SerializeToString(&bytes);

    uint32 *dest = reinterpret_cast<uint32*>(send_buffer);
    char *data = send_buffer + sizeof(uint32);
    memcpy(data, bytes.data(), bytes.size());

    for (int i = 0 ; i < num_server ; i++) {
        *dest = num_agent + 1 + i;
        sender.Send(send_buffer, bytes.size() + sizeof(uint32));
    }
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int m_rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &m_rank);

    if (m_rank == 1) { // Agent
        cout << "I'm agent" << endl;

        char send_buffer[MAX_BUFFER_SIZE];
        AveragePartition p(max_features, num_server);
        TextReader reader(&p);
        reader.OpenFile(double_test);
        MPICommunicator sender;
        sender.Initialize("Agent",
                          MAX_BUFFER_SIZE,
                          MAX_QUEUE_SIZE,
                          MAX_QUEUE_SIZE);
        while (true) {
            Message msg;
            if (!reader.Read(msg)) break;
            HeadMessage *ptr_hm = msg.mutable_head();
            ptr_hm->set_worker_id(1);
            string bytes;
            msg.SerializeToString(&bytes);
            
            uint32* dest = reinterpret_cast<uint32*>(send_buffer);
            char *data = send_buffer + sizeof(uint32);

            *dest = p.Shard(ptr_hm->start_index()) + num_agent + 1;
            memcpy(data, bytes.data(), bytes.size());

            sender.Send(send_buffer, bytes.size() + sizeof(uint32));
        }
        NotifyFinished(sender, send_buffer);
        sleep(1);
        NotifyFinished(sender, send_buffer);
        sender.Finalize();
        cout << "agent finalized. " << endl;
    }
    else if (m_rank == 2 || m_rank == 3) { // server
        
        cout << "I'm server" << endl;

        MPICommunicator recver;
        recver.Initialize("Server",
                          MAX_BUFFER_SIZE,
                          MAX_QUEUE_SIZE,
                          MAX_QUEUE_SIZE);

        char recv_buffer[MAX_BUFFER_SIZE];
        while (true) {
            int receive_bytes = recver.Receive(recv_buffer, MAX_BUFFER_SIZE);
            Message msg;
            CHECK(msg.ParseFromArray(recv_buffer, receive_bytes));
            HeadMessage *ptr_hm = msg.mutable_head();
            if (ptr_hm->start_index() == -1) break;
            cout << "worker id: " << ptr_hm->worker_id() << endl;
            cout << "start index: " << ptr_hm->start_index() << endl;
            for (int i = 0 ; i < msg.list_size(); i++) {
                cout << msg.list(i) << endl;
            }
        }
        recver.Finalize();
        cout << "server finalzied. " << endl;
        
    }
    else { // master
        cout << "I'm master" << endl;
        cout << "Master finalized." << endl;
    }
  
    MPI_Finalize();

    return 0;
}
