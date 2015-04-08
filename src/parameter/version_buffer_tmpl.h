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

    SparseMatrixImpl(int bounded) 
    : bounded_staleness_(bounded) {

    }

    ~SparseMatrixImpl() {}

    void Set(int iter_num, KeyType& key, ValueType& value);

private:

    scoped_ptr<SparseMatrixImpl> buffer_;       // the buffer to store the version update data.
    int oldest_pointer_;                        // current_pointer_ record which row store the oldest updates.
    int oldest_iteration_;                      // the oldest number of iteration.
    int bounded_staleness_;                     // bounded_staleness_ decide the row size of buffer. 
                                                // row_size = bounded_staleness_ + 1.

    std::vector<uint32> agent_timestap;         // record the current timestap (iteration) of each agent worker.
    std::map<uint32, uint32> iter_to_row;       // mapping number of iteration to number of row.
};

} // namespace brook

#endif // PARAMETER_VERSION_BUFFER_TMPL_H_
