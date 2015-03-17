// Copyright : 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
// Define the interface of Puller. Puller can read data from in_memory
// file and send data to parameter server.
//
#ifndef CORE_PULLER_H_
#define CORE_PULLER_H_

#include <string>

#include "src/agent/reader.h"
#include "src/message/message.pb.h"


namespace brook {

const int kAgentSendTag = 1;

class Pusher {
public:
    Pusher(std::string filename) : filename_(filename) {
        reader_.Open(filename_.c_str());
    }
    ~Pusher() {};

    void Send();

private:

    void NotifyFinished();
    int Shard(uint64 index);
    std::string filename_;
    TextReader reader_;
    SendMessage sm_;

};

} // namespace brook

#endif // CORE_PULLER_H_
