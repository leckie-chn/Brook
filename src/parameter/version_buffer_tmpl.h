// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef PARAMETER_VERSION_BUFFER_TMPL_H_
#define PARAMETER_VERSION_BUFFER_TMPL_H_

#include "src/parameter/random_queue_tmpl.h"
#include "src/parameter/skip_list_tmpl.h"
#include "src/parameter/dense_vector_tmpl.h"
#include "src/util/common.h"
#include "src/util/scoped_ptr.h"
#include "src/util/bitmap.h"

#include <vector>
#include <map>
#include <set>

namespace brook {

//-----------------------------------------------------------------------
// VersionBuffer is used to store the updates in different iteration.
//-----------------------------------------------------------------------
template <class ValueType>
class VersionBufferTmpl {

typedef SkipListQueueTmpl<ValueType> RandomQueue; 
typedef DenseVectorTmpl<ValueType> DenseVector;
typedef std::vector<Bitmap> BitmapList;
typedef std::vector<uint64> IntList;
typedef std::vector<RandomQueue> RandomQueueList;

public:

    VersionBufferTmpl(uint64 feature_num, int bit_size, int num_agent) {
        CHECK_GT(bit_size, 0);
        CHECK_GT(feature_num, 0);
        CHECK_GT(num_agent, 0);
        
        feature_num_ = feature_num;
        bit_size_ = bit_size;
        current_iteration_ = 0;
        num_agent_ = num_agent;
    
        buffer_.reset(new RandomQueueList(feature_num_, RandomQueue()));
        accessing_table_.reset(new BitmapList(feature_num_, Bitmap(bit_size_)));
        oldest_update_.reset(new DenseVector(feature_num_, 0));
    }
    
    ~VersionBufferTmpl() {}

    void Set(uint64 key, uint32 iter_num, ValueType value);

    const ValueType Get(uint64 key, uint32 iter_num);
   
    void InsertUpdate(int worker_id, uint64 key, ValueType value);

    DenseVector* GetOldestUpdates();
    RandomQueueList* GetBuffer() { return buffer_.get(); }

    std::map<uint32, uint32>& GetAgentTimestamp();

    void AddAgentTimestamp(uint32 worker_id);

    void AddFinishedCount(uint32 iteration);

    bool CurrentIterationFinished();
    
private:

    scoped_ptr<RandomQueueList> buffer_;        // the buffer to store the version update data.
    scoped_ptr<BitmapList> accessing_table_;    // to record each parameter has been accessed by a 
                                                // list (bitmap) of agent.

    scoped_ptr<DenseVector> oldest_update_;     // to store the oldest update.
    uint32 current_iteration_;                  // record the number of current iteration.
                             
    uint32 bit_size_;                           // the size of each bitmap.
    uint64 feature_num_;                        // the size of parameter, this may be vary large.
    uint32 num_agent_;                          // the number of agent workers.

    std::map<uint32, uint32> agent_timestap_;   // record the current timestap (iteration) of each agent worker.
    std::map<uint32, uint32> finished_;         // make the record of finished agent count for every iteration.
};

template <class ValueType>
void VersionBufferTmpl<ValueType>::Set(uint64 key, uint32 index, ValueType value) {
    CHECK_LE(index, (*buffer_)[key].Size());

    if (index < (*buffer_)[key].Size()) {    // Update old value
        (*buffer_)[key].Set(index, value);
    } 
    else {   // Insert new value
        (*buffer_)[key].Push(value);
    }
}

template <class ValueType>
const ValueType VersionBufferTmpl<ValueType>::Get(uint64 key, uint32 index) {
    CHECK_GE(index, 0);
    CHECK_LE(index, (*buffer_)[key].Size());
    if (index < (*buffer_)[key].Size()) {
        return (*buffer_)[key].Get(index);
    }
    else {
        return 0;
    }
}

template <class ValueType>
void VersionBufferTmpl<ValueType>::InsertUpdate(int worker_id, uint64 key, ValueType value) {
    CHECK_GE(worker_id, 0);
    CHECK_LE(worker_id, num_agent_);
    
    int timestap = agent_timestap_[worker_id]; 
    int index = timestap - current_iteration_;
    Set(key, index, value + Get(key, index));              // Add new update to the buffer

    if (timestap == 0) {                                   // At the first iteration, we need to make the sample.
        (*accessing_table_)[key].SetElement(worker_id);
    }
}

template <class ValueType>
DenseVectorTmpl<ValueType>* VersionBufferTmpl<ValueType>::GetOldestUpdates() {
    for (uint64 i = 0 ; i < feature_num_ ; i++) {
        (*oldest_update_)[i] = (*buffer_)[i].Pop();
    }
    current_iteration_++;
    return oldest_update_.get();
}

template <class ValueType>
std::map<uint32, uint32>& VersionBufferTmpl<ValueType>::GetAgentTimestamp() {
    return agent_timestap_;
}

template <class ValueType>
void VersionBufferTmpl<ValueType>::AddAgentTimestamp(uint32 worker_id) {
    agent_timestap_[worker_id]++;
}

template <class ValueType>
void VersionBufferTmpl<ValueType>::AddFinishedCount(uint32 iteration) {
    finished_[iteration]++;
}

template <class ValueType>
bool VersionBufferTmpl<ValueType>::CurrentIterationFinished() {
    return finished_[current_iteration_] == num_agent_;
}

} // namespace brook

#endif // PARAMETER_VERSION_BUFFER_TMPL_H_
