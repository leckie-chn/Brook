// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
// Define the class template SparseVectorImpl and operations required
// by users.
//
#ifndef PARAMETER_SPARSE_VECTOR_TMPL_H_
#define PARAMETER_SPARSE_VECTOR_TMPL_H_
#include <map>

namespace brook {

using std::map;
using std::pair;
using std::ostream;

// We use std::map as the container of a sparse vector. Because
// std::map implements a sorting tree (RB-tree), so its iterator
// accesses elements in known order of keys. This is important for
// sparse vector operations like dot-product and add-multi-into.
// The ValueType must be a numberical type supporting const 0.
template<class KeyType, class ValueType>
class SparseVectorImpl : public map<KeyType, ValueType> {

};

} // namespace


#endif // PARAMETER_SPARSE_VECTOR_TMPL_H_
