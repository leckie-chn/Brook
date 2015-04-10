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
#include <set>

namespace brook {

//-----------------------------------------------------------------------
// VersionBuffer is used to store the updates in different iteration.
//-----------------------------------------------------------------------
template <class ValueType>
class VersionBuffer {

typedef RandomQueueTmpl<ValueType> RandomQueue;    
typedef DenseVectorTmpl<ValueType> DenseVector;
typedef std::vector<Bitmap> BitmapList;
typedef std::vector<uint64> IntList;
typedef std::vector<RandomQueue> RandomQueueList;

public:

    VersionBuffer(uint64 feature_num, int bit_size, int num_agent) {
        CHECK_GT(bit_size, 0);
        CHECK_GT(feature_num, 0);
        CHECK_GT(num_agent, 0);
        
        feature_num_ = feature_num;
        bit_size_ = bit_size;
        current_iteration_ = 0;
        num_agent_ = num_agent;
        update_count_ = 0;
    
        buffer_.reset(new RandomQueueList(feature_num_));
        accessing_table_.reset(new BitmapList(feature_num_, Bitmap(bit_size_)));
        oldest_update_.reset(new DenseVector(feature_num_, 0));
        update_count_iter.reset(new IntList(1, 0));
    }
    
    ~VersionBuffer() {}

    void Set(uint64 key, uint32 iter_num, ValueType& value);

    const ValueType& Get(uint64 key, uint32 iter_num);

    /* return: 
     * true  : current iteration finished.
     * false : current iteration not finished. 
     */
    bool InsertUpdate(int worker_id, uint64 key, ValueType& value);

    DenseVector& GetOldestUpdates();

    std::map<uint32, uint32>& GetAgentTimestamp();

private:

    scoped_ptr<RandomQueueList> buffer_;        // the buffer to store the version update data.
    scoped_ptr<BitmapList> accessing_table_;    // to record each parameter has been accessed by a 
                                                // list (bitmap) of agent.

    scoped_ptr<DenseVector> oldest_update_;     // to store the oldest update.
    uint32 current_iteration_;                  // record the number of current iteration.
                             
    uint32 bit_size_;                           // the size of each bitmap.
    uint64 feature_num_;                        // the size of parameter, this may be vary large.
    uint32 num_agent_;                          // the number of agent workers.
    
    uint64 update_count_;
    scoped_ptr<IntList> update_count_iter;

    std::map<uint32, uint32> agent_timestap_;   // record the current timestap (iteration) of each agent worker.
    std::set<uint32> finished_agent_;           // we need record the finished agent at the first iteration.
};

template <class ValueType>
void VersionBuffer<ValueType>::Set(uint64 key, uint32 index, ValueType& value) {
    if (index < (*buffer_)[key].Size()) {    // Update old value
        (*buffer_)[key].Set(index, value);
    } 
    else {   // Insert a value
        (*buffer_)[key].Push(value);
    }
}

template <class ValueType>
const ValueType& VersionBuffer<ValueType>::Get(uint64 key, uint32 index) {
    return (*buffer_)[key].Get(index);
}

template <class ValueType>
bool VersionBuffer<ValueType>::InsertUpdate(int worker_id, uint64 key, ValueType& value) {
    CHECK_GT(worker_id, 1);
    CHECK_LE(worker_id, num_agent_);

    if (key == -1) { // the final signal
        agent_timestap_[worker_id]++;
        if (current_iteration_ == 0) {
            finished_agent_.insert(worker_id);
            if (finished_agent_.size() >= num_agent_) { // In the first iteration, we must wait all agent send the 
                finished_agent_.clear();                // final signal and return true.
                return true;                            
            }
        }
    }
    else {
        int timestap = agent_timestap_[worker_id]; 
        int index = timestap - current_iteration_;
        Set(key, index, value + Get(index));                   // Add new update to the buffer

        if (timestap == 0) {                                   // At the first iteration, we need to make the sample.
            (*accessing_table_)[key].SetElement(worker_id);
            update_count_++;
        }
        else {
            if (timestap >= update_count_iter->size()) {
                update_count_iter->push_back(1);
            }
            else (*update_count_iter)[timestap]++;
        }
        if (current_iteration_ != 0 && update_count_iter[current_iteration_] == update_count_) { // we can return true;
            return true;
        }
    }

    return false;
}

template <class ValueType>
DenseVectorTmpl<ValueType>& VersionBuffer<ValueType>::GetOldestUpdates() {
    for (uint64 i = 0 ; i < feature_num_ ; i++) {
        oldest_update_[i] = buffer_[i].Pop();
    }
    current_iteration_++;
    return oldest_update_;
}

template <class ValueType>
std::map<uint32, uint32>& VersionBuffer<ValueType>::GetAgentTimestamp() {
    return agent_timestap_;
}

} // namespace brook

#endif // PARAMETER_VERSION_BUFFER_TMPL_H_
