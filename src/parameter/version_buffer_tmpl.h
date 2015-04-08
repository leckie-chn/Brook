// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef PARAMETER_VERSION_BUFFER_TMPL_H_
#define PARAMETER_VERSION_BUFFER_TMPL_H_

#include "src/parameter/sparse_matrix_tmpl.h"
#include "src/util/common.h"
#include "src/util/scoped_ptr.h"

#include <vector>

namespace brook {

//-----------------------------------------------------------------------
// VersionBuffer is used to store the updates in different iteration.
//-----------------------------------------------------------------------
template <class KeyType, class ValueType>
class VersionBuffer {

typedef SparseMatrixImpl<KeyType, ValueType> SparseMatrixImpl;

public:

    VersionBuffer(int bounded, int num_agent) {
        CHECK_GT(num_agent, 0);
        CHECK_GE(bounded, 0);

        bounded_staleness_ = bounded;
        row_size_ = bounded_staleness_ + 1;
        num_agent_ = num_agent;
        buffer_.reset(new SparseMatrixImpl(bounded_staleness_+1));
        agent_timestap.resize(num_agent_, 0);
        oldest_pointer_ = 0;
        oldest_iteration_ = 0;

        for (int i = 0 ; i < row_size_ ; i++) {
            iter_to_row[i] = i;
        }
    }

    ~VersionBuffer() {}


    void Set(int row, KeyType& key, ValueType& value);

    void InsertUpdate(int worker_id, KeyType& key, ValueType& value);

private:

    scoped_ptr<SparseMatrixImpl> buffer_;       // the buffer to store the version update data.
    int oldest_pointer_;                        // current_pointer_ record which row store the oldest updates.
    int oldest_iteration_;                      // the oldest number of iteration.
    int bounded_staleness_;                     // bounded_staleness_ decide the row size of buffer. 
                                                // row_size = bounded_staleness_ + 1.
    int row_size_;

    std::vector<uint32> agent_timestap;         // record the current timestap (iteration) of each agent worker.
                                                // NOTE: the real index of worker is index + 1, beacause we remove
                                                // master node.
    std::map<uint32, uint32> iter_to_row;       // mapping number of iteration to number of row.
    int num_agent_;
};

template <class KeyType, class ValueType>
void VersionBuffer<KeyType, ValueType>::Set(int row, KeyType& key, ValueType& value) {
    (*buffer_)[row].set(key, value);
}

template <class KeyType, class ValueType>
void VersionBuffer<KeyType, ValueType>::InsertUpdate(int worker_id, KeyType& key, ValueType& value) {
    agent_timestap[worker_id - 1] // NOTE: real id is index + 1, beacause we remove master node here.
    
}

} // namespace brook

#endif // PARAMETER_VERSION_BUFFER_TMPL_H_
