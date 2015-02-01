// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
// VectorIterator is a interface which 
// used for broadcasting model. 
//
#ifndef IN_MEMORY_STORE_VECTOR_ITERATOR_H_
#define IN_MEMORY_STORE_VECTOR_ITERATOR_H_

#include "src/common/base.h"

#include "src/in_memory_store/sparse_vector.h"
#include "src/in_memory_store/dense_vector.h"

#include <string>

namespace brook {

typedef SparseVector<KeyType, ValueType> SV;
typedef DenseVector<ValueType> DV;

template <class KeyType, class ValueType>
class SparseVectorIterator {
public:
    SparseVectorIterator() {}
    ~SparseVectorIterator() {}

    Initialize(typename SV* sv_ptr);
    HasNext(std::string& key, std::string& value);

private:
    typename SV* sv_;
    typename SV::const_iterator iter_;
    DIS_ALLOW_COPY_AND_ASSIGN(SparseVectorIterator);
};

template <class ValueType>
class DenseVectorIterator {
public:
    DenseVectorIterator() {}
    ~DenseVectorIterator() {}

    Initialize(typename DV* dv_ptr);
    HasNext(std::string& key, std::string& value);

private:
    typename DV* dv_;
    typename DV::const_iterator iter_;
    uint32 index_;
    DIS_ALLOW_COPY_AND_ASSIGN(DenseVectorIterator);
};

} // namespace brook

#endif // IN_MEMORY_STORE_VECTOR_ITERATOR_H_
