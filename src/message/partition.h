// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef MESSAGE_PARTITION_H_
#define MESSAGE_PARTITION_H_

#include "src/util/common.h"

namespace brook {

class Partition {
public:
   
    Partition() {}

    Partition(uint64 mf, int ns, int na) 
    : max_feature_(mf), num_server_(ns), num_agent_(na) {}

    int NaiveShard(uint64 index) {
        return index / (max_feature_ / num_server_) + num_agent_ + 1;
    }

private:
    uint64 max_feature_;
    int num_server_;
    int num_agent_;
};

} // namespace brook

#endif // MESSAGE_PARTITION_H_
