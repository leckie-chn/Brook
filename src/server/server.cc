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

#include "src/main/flags.h"
#include "src/base/scoped_ptr.h"
#include "src/base/common.h"
#include "src/message/message.pb.h"
#include "src/strutil/join_strings.h"
#include "src/sorted_buffer/sorted_buffer.h"
#include "src/sorted_buffer/sorted_buffer_iterator.h"
#include "src/in_memory_store/dense_table.h"

namespace brook {

using std::map;
using std::string;
using std::vector;
using sorted_buffer::SortedBuffer;
using::sorted_buffer::SortedBufferIteratorImpl;

bool ServerInitialize() {
    
    LOG(INFO) << "Server initialize.";

    return true;
}

void ServerFinalize() {
    LOG(INFO) << "Server finalize.";
}


void ServerService() {
    
    if (!ServerInitialize()) {
        LOG(FATAL) << "Server Initialize failed.";
    }

    LOG(INFO) << "Server service start.";

    ServerFinalize();
}

} // namespace brook
