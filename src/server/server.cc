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
}

void ServerService() {
    
    if (!ServerInitialize()) {
        LOG(FATAL) << "Server Initialize failed.";
    }

    LOG(INFO) << "Server service start.";

    ServerFinalize();
}

} // namespace brook
