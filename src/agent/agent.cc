// Copyright : 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/agent/agent.h"

#include <stdio.h>

#include <map>
#include <new>
#include <string>
#include <vector>

#include "src/core/flags.h"
#include "src/base/scoped_ptr.h"
#include "src/base/common.h"
#include "src/agent/reader.h"
#include "src/message/message.pb.h"

namespace brook {

using std::map;
using std::string;
using std::vector;

bool AgentInitialize() {


    return true;
}

//-------------------------------------------------------
// Implementation of agent send work.
//-------------------------------------------------------
void SendWork() {
    // By default, we create a TextReader.
    // Maybe we will implemente the RecordReader in the future.
    scoped_ptr<Reader> reader(new TextReader());
    if (reader.get() == NULL) {
        LOG(FATAL) << "Creating reader error.";
    }
    reader->Open(SubDataCacheFile().c_str());

    SendMessage sm;
    while (true) {
        if (!reader->Read(&sm)) {
            break;
        }

    }

    
}



void AgentService() {
    
}    

void AgentFinalize() {

}

} // namespace brook
