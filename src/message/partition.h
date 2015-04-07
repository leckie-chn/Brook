// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef MESSAGE_PARTITION_H_
#define MESSAGE_PARTITION_H_

#include "src/util/common.h"

namespace brook {

//--------------------------------------------------------------------------
// Partition is an abstrace class that implemented by `real` partitions.
// This class decides which server the current message will be sent to.
//--------------------------------------------------------------------------
class Partition {
public:
    Partition(uint64 n_f, uint32 n_s) 
    : num_features_(n_f), num_servers_(n_s) {}

    virtual uint32 Shard(uint64 index) = 0; 

private:
    uint64 num_features_;
    uint32 num_servers_;
};

//--------------------------------------------------------------------------
// AveragePartition is a easy but efficient mechanism.
// For example, there are 2 servers, and the list of parameter index is :
// { 0, 1, 2, 5, 7, 9, 10, 11, 12, 15, 16 }
// using AveragePartition, { 0, 1, 2, 5, 7 } will be sent to server_1,
// { 9, 10, 11, 12, 15, 16 } will be sent to server_2.
//--------------------------------------------------------------------------
class AveragePartition : public Partion {
public:
    virtual uint32 Shard(uint64 index) {
        return index / (num_features_ / num_servers_);
    }
};    

} // namespace brook

#endif // MESSAGE_PARTITION_H_
