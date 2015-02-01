// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
// VectorIterator is a interface which 
// used for broadcasting model. 
//
#ifndef IN_MEMORY_STORE_VECTOR_ITERATOR_H_
#define IN_MEMORY_STORE_VECTOR_ITERATOR_H_

#include "src/base/common.h"

#include "src/in_memory_store/sparse_vector.h"
#include "src/in_memory_store/dense_vector.h"

#include <sstream>
#include <string>

namespace brook {

template <class KeyType, class ValueType>
class SparseVectorIterator {
public:
    SparseVectorIterator() {}
    ~SparseVectorIterator() {}

    void Initialize(SparseVector<KeyType, ValueType>* sv_ptr) {
        this->sv_ = sv_ptr;
        this->iter_ = sv_->begin();
    }
    bool HasNext(std::string& key, std::string& value) {
        if (iter_ != sv_->end()) {
            // get key
            key = iter_->first;
            // get value
            std::ostringstream os;
            os << static_cast<ValueType>(iter_->second);
            value = os.str();
            iter_++;
            return true;
        }
        return false;
    }

private:
    SparseVector<KeyType, ValueType>* sv_;
    typename SparseVector<KeyType, ValueType>::const_iterator iter_;
    DISALLOW_COPY_AND_ASSIGN(SparseVectorIterator);
};

template <class ValueType>
class DenseVectorIterator {
public:
    DenseVectorIterator() {}
    ~DenseVectorIterator() {}

    void Initialize(DenseVector<ValueType>* dv_ptr);
    bool HasNext(std::string& key, std::string& value);

private:
    DenseVector<ValueType>* dv_;
    typename DenseVector<ValueType>::const_iterator iter_;
    uint32 index_;
    DISALLOW_COPY_AND_ASSIGN(DenseVectorIterator);
};

} // namespace brook

#endif // IN_MEMORY_STORE_VECTOR_ITERATOR_H_
