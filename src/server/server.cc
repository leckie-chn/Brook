// Copright: 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/server/server.h"

#include <mpi.h>

#include <stdio.h>

#include <map>
#include <new>
#include <string>
#include <vector>

#include "src/core/flags.h"
#include "src/base/scoped_ptr.h"
#include "src/base/common.h"
#include "src/message/message.pb.h"
#include "src/strutil/join_strings.h"
#include "src/sorted_buffer/sorted_buffer.h"
#include "src/sorted_buffer/sorted_buffer_iterator.h"

namespace brook {

using std::map;
using std::string;
using std::vector;
using sorted_buffer::SortedBuffer;
using::sorted_buffer::SortedBufferIteratorImpl;

//-------------------------------------------------------------------------------------
// Constants used by server:
//-------------------------------------------------------------------------------------

const int kServerRecvTag = 1;


//-------------------------------------------------------------------------------------
// The buffer used by a server worker process to recieve a agent output message.
//-------------------------------------------------------------------------------------
char* output_recieve_buffer = NULL;


bool ServerInitialize() {
    
    LOG(INFO) << "Server initialize.";

    return true;
}

void ServerFinalize() {

    LOG(INFO) << "Server finalize.";

}

void ReceiveWork() {
    LOG(INFO) << "Receive in " 
              << (SortBasedShuffle() ? "sorted_shuffle" : "hash_shuffle")
              << " model.";
    LOG(INFO) << "Output to " << JoinStrings(OutputFiles(), ",");

    // Once a agent worker finished processing its its shard, it will
    // send a 'finished' message to all server workers. A server worker
    // collects sucj messages into finished_agent_worker. After 'finished'
    // message from all agent workers are collectedm the receive work quits.
    std::set<int> finished_agent_workers;

    // Used for Sorted_based shuffle
    SortedBuffer* server_input_buffer = NULL;

    // Used for Hash_based shuffle
    typedef map<uint64, double> AggregationTable;
    AggregationTable* aggregation_table = NULL;

    // Initialize aggregation_table or sorted_buffer.
    if (!SortBasedShuffle()) {
        aggregation_table = new AggregationTable;
    } else {
        try {
            LOG(INFO) << "Creating server input buffer ... filebase = "
                      << ServerInputBufferFilebase()
                      << ", buffer size cap = "
                      << ServerInputBufferSize();
            server_input_buffer = new SortedBuffer(
                ServerInputBufferFilebase(),
                ServerInputBufferSize());
        } catch (const std::bad_alloc&) {
            LOG(FATAL) << "Insufficient memory for creating server input buffer.";
        }
        LOG(INFO) << "Succeeded creating server input buffer.";
    }

    // Allocate agent outputs recieving buffer.
    LOG(INFO) << "Creating agent output recieving buffer ...";
    CHECK_LT(0, MaxAgentOutputBufferSize());
    try {
        output_recieve_buffer = new char[MaxAgentOutputBufferSize()];
    } catch (const std::bad_alloc&) {
        LOG(FATAL) << "Insufficient memory for agent output recieving buffer.";
    }
    LOG(INFO) << "Succeeded creating agent output recieving buffer.";

    // Loop over agent outputs arrived in this server worker.
    LOG(INFO) << "Start recieving and processing arriving agent outputs ...";
    MPI_Status status;

    int32 recieved_bytes = 0;

    while (true) {
        MPI_Recv(output_recieve_buffer, 
                 MaxAgentOutputBufferSize(),
                 MPI_CHAR,
                 MPI_ANY_SOURCE,
                 kServerRecvTag, MPI_COMM_WORLD, &status);
    
        MPI_Get_count(&status, MPI_CHAR, &recieved_bytes);

        if (recieved_bytes >= MaxAgentOutputBufferSize()) {
            LOG(FATAL) << "MPI_Recieving a proto message with size (at least) "
                       << recieved_bytes
                       << ", which >= FLAGS_max_output_size ("
                       << MaxAgentOutputBufferSize() << ")."
                       << "You can modify FLAGS_max_output_size defined in "
                       << __FILE__;
        }

        SendMessage sm;
        CHECK(sm.ParseFromArray(output_recieve_buffer,
                            recieved_bytes));

        // Final signal
        if (sm.has_agent_worker()) {
            finished_agent_workers.insert(sm.agent_worker());
            if (finished_agent_workers.size() >= NumAgentWorkers()) {
                LOG(INFO) << "Finished recieving agent agent outputs.";
                break; // Break the while (true) loop.
            }
        } else {
            CHECK(sm.has_index());
            CHECK(sm.has_list());

            // Hash_based shuffle
            if (!SortBasedShuffle()) {
                
            } else { // Sorted_based shuffle

            }
        }
    }
    
}

void ServerService() {
    
    if (!ServerInitialize()) {
        LOG(FATAL) << "Server Initialize failed.";
    }

    LOG(INFO) << "Server service start.";

    ServerFinalize();
}

} // namespace brook
