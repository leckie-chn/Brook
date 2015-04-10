// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef PARAMETER_VERSION_BUFFER_TMPL_H_
#define PARAMETER_VERSION_BUFFER_TMPL_H_

#include "src/parameter/random_queue_tmpl.h"
#include "src/parameter/dense_vector_tmpl.h"
#include "src/util/common.h"
#include "src/util/scoped_ptr.h"
#include "src/util/bitmap.h"

#include <vector>
#include <map>

namespace brook {

//-----------------------------------------------------------------------
// VersionBuffer is used to store the updates in different iteration.
//-----------------------------------------------------------------------
template <class ValueType>
class VersionBuffer {

typedef RandomQueueTmpl<ValueType> RandomQueue;    
typedef DenseVectorTmpl<ValueType> DenseVector;
typedef std::vector<Bitmap> BitmapList;
typedef std::vector<uint32> IntList;
typedef std::vector<RandomQueue> RandomQueueList;

public:

    VersionBuffer(uint64 feature_num, int bit_size, int num_agent) {
        CHECK_GT(bit_size, 0);
        CHECK_GT(feature_num, 0);
        CHECK_GT(num_agent, 0);
        
        feature_num_ = feature_num;
        bit_size_ = bit_size;
        finished_count_ = 0;
        num_agent_ = num_agent;
    
        buffer_.reset(new RandomQueueList(feature_num_));
        accessing_table_.reset(new BitmapList(feature_num_, Bitmap(bit_size_)));
        accessing_count_.reset(new IntList(feature_num_, 0));
        oldest_update_.reset(new DenseVector(feature_num_, 0));

    }
    
    ~VersionBuffer() {}

    void Set(uint64 key, uint32 iter_num, ValueType& value);

    const ValueType& Get(uint64 key, uint32 iter_num);

    void InsertUpdate(int worker_id, uint64 key, ValueType& value);

    DenseVector& GetOldestUpdates();

    std::map<uint32, uint32>& GetAgentTimestamp();

private:

    scoped_ptr<RandomQueueList> buffer_;        // the buffer to store the version update data.
    scoped_ptr<BitmapList> accessing_table_;    // to record each parameter has been accessed by a 
                                                // list (bitmap) of agent.
    scoped_ptr<IntList> accessing_count_;       // to record the number of each parameter been accessed.

    scoped_ptr<DenseVector> oldest_update_;     // to store the oldest update.
    uint32 finished_count_;                     // record how many iterations has been finished.
                             
    uint32 bit_size_;                           // the size of each bitmap.
    uint64 feature_num_;                        // the size of parameter, this may be vary large.
    uint32 num_agent_;

    std::map<uint32, uint32> agent_timestap_;   // record the current timestap (iteration) of each agent worker.
};

template <class ValueType>
void VersionBuffer<ValueType>::Set(uint64 key, uint32 index, ValueType& value) {
    (*buffer_)[key].Set(index, value);
}

template <class ValueType>
const ValueType& VersionBuffer<ValueType>::Get(uint64 key, uint32 index) {
    return (*buffer_)[key].Get(index);
}

template <class ValueType>
void VersionBuffer<ValueType>::InsertUpdate(int worker_id, uint64 key, ValueType& value) {
    CHECK_GT(worker_id, 1);
    CHECK_LE(worker_id, num_agent_);

    int timestap = agent_timestap_[worker_id]; 
    int index = timestap - finished_count_;
    Set(key, index, value + Get(index));    // Add new update to the buffer

    if (timestap == 0) {                    // At the first iteration, we need to make the record.
        (*accessing_table_)[key].SetElement(worker_id);
        (*accessing_count_)[key]++;
    }
}

template <class ValueType>
DenseVectorTmpl<ValueType>& VersionBuffer<ValueType>::GetOldestUpdates() {
    for (uint64 i = 0 ; i < feature_num_ ; i++) {
        oldest_update_[i] = buffer_[i].Pop();
    }
    finished_count_++;
    return oldest_update_;
}

template <class ValueType>
std::map<uint32, uint32>& VersionBuffer<ValueType>::GetAgentTimestamp() {
    return agent_timestap_;
}

} // namespace brook

#endif // PARAMETER_VERSION_BUFFER_TMPL_H_
