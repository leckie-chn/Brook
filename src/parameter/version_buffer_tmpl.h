// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef PARAMETER_VERSION_BUFFER_TMPL_H_
#define PARAMETER_VERSION_BUFFER_TMPL_H_

#include "src/parameter/dense_matrix_tmpl.h"
#include "src/util/common.h"
#include "src/util/scoped_ptr.h"

#include <vector>
#include <map>

namespace brook {

//-----------------------------------------------------------------------
// VersionBuffer is used to store the updates in different iteration.
//-----------------------------------------------------------------------
template <class ValueType>
class VersionBuffer {

typedef DenseMatrixImpl<ValueType> DenseMatrixImpl;

public:

    VersionBuffer(int bounded, uint64 feature_num, int num_agent) {
        CHECK_GT(num_agent, 0);
        CHECK_GE(bounded, 0);
        CHECK_GT(feature_num, 0);

        bounded_staleness_ = bounded;
        row_size_ = bounded_staleness_ + 1;
        feature_num_ = feature_num;
        num_agent_ = num_agent;

        buffer_.reset(new DenseMatrixImpl(row_size_), feature_num, 0);
        agent_timestap_.resize(num_agent_, 0);
        oldest_pointer_ = 0;
        oldest_iteration_ = 0;

        for (int i = 0 ; i < row_size_ ; i++) {
            iter_to_row_[i] = i;
        }
    }

    ~VersionBuffer() {}


    void Set(int row, uint64 key, ValueType& value);

    const ValueType& Get(int row, uint64 key);

    void InsertUpdate(int worker_id, uint64 key, ValueType& value);

private:

    scoped_ptr<DenseMatrixImpl> buffer_;       // the buffer to store the version update data.
    int oldest_pointer_;                        // current_pointer_ record which row store the oldest updates.
    int oldest_iteration_;                      // the oldest number of iteration.
    int bounded_staleness_;                     // bounded_staleness_ decide the row size of buffer. 
                                                // row_size = bounded_staleness_ + 1.
    int row_size_;
    uint64 feature_num_;

    std::vector<uint32> agent_timestap_;         // record the current timestap (iteration) of each agent worker.
                                                 // NOTE: the real index of worker is index + 1, beacause we remove
                                                 // master node.
    std::map<uint32, uint32> iter_to_row_;       // mapping number of iteration to number of row.
    int num_agent_;
};

template <class ValueType>
void VersionBuffer<ValueType>::Set(int row, uint64 key, ValueType& value) {
    (*buffer_)[row][key] = value;
}

template <class ValueType>
const ValueType& VersionBuffer<ValueType>::Get(int row, uint64 key) {
    return (*buffer_)[row][key];
}

template <class ValueType>
void VersionBuffer<ValueType>::InsertUpdate(int worker_id, uint64 key, ValueType& value) {
    CHECK_GT(worker_id, 1);
    CHECK_LE(worker_id, num_agent_);

    int timestap = agent_timestap_[worker_id - 1]; // NOTE: real worker id is index + 1, 
                                                   // beacause we remove master node here.
    int row = iter_to_row_[timestap];
    Set(row, key, value + Get(row));   // Add new value to the buffer
}

} // namespace brook

#endif // PARAMETER_VERSION_BUFFER_TMPL_H_
