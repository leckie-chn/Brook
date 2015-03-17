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

namespace brook {

using std::map;
using std::string;
using std::vector;
using sorted_buffer::SortedBuffer;

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
        
    } else {

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
