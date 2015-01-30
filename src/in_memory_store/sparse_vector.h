// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
// SpaseVector is used to store the sparse model which actually using the map 
// data structure. The random accessing performance of SparseVector is
// lower than DenseVector but it is more space effcient.
//
#ifndef IN_MEMORY_STORE_SPARSE_VECTOR_H_
#define IN_MEMORY_STORE_SPARSE_VECTOR_H_

#include <map>

namespace brook {

using std::map;
using std::pair;
using std::ostream;

// We use std::map as the contaniner of a sparse vector. Because
// std::map implements a sorting tree (RB-tree), so its iterator
// accesses elements in known order of keys. This is importance for
// sparse vector operations like dot-product and add-multi-into.
// The ValueType must be a numeric type supporting const 0.
template <class KeyType, class ValueType>
class SparseVector : public map<KeyType, ValueType> {
public:
    typedef typename map<KeyType, ValueType>::const_iterator const_iterator;
    typedef typename map<KeyType, ValueType>::iterator iterator;

    // We constrain operator[] a read-only operations to prevent
    // accidential insert of elements.
    const 
};


} // namespace brook
 
#endif // IN_MEMORY_STORE_SPARSE_VECTOR_H_
