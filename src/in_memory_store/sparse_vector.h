// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
// SparseVector is used to store the sparse model which actually using the map 
// data structure. The random accessing performance of SparseVector is
// lower than DenseVector but it is more space effcient.
//
#ifndef IN_MEMORY_STORE_SPARSE_VECTOR_H_
#define IN_MEMORY_STORE_SPARSE_VECTOR_H_

#include <map>
#include <iostream>

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
    const ValueType& operator[] (const KeyType& key) const {
        const_iterator iter = this->find(key);
        if (iter == this->end()) {
            return zero_;
        }
        return iter->second;
    }

    // Set a value at given key. If value == 0, an existing key-value
    // pair is removed. If value != 0, the value is set or inserted.
    // This function also serves as a convenient form insert(), no
    // need to use std::pair.
    void set(const KeyType& key, const ValueType& value) {
        iterator iter = this->find(key);
        if (iter != this->end()) {
            if (IsZero(value)) {
                this->erase(iter);
            } else {
                iter->second = value;
            }
        } else {
            if (!IsZero(value)) {
                this->insert(pair<KeyType, ValueType>(key, value));
            }
        }
    }

    bool has(const KeyType& key) const {
        return this->find(key) != this->end();
    }

protected:
    static const ValueType zero_;

    static bool IsZero(const ValueType& value) {
        return value == 0;
    }
};

template<class KeyType, class ValueType> 
const ValueType SparseVector<KeyType, ValueType>::zero_(0);

// Scale(v,c) : v <- v * c
template <class KeyType, class ValueType, class ScaleType> 
void Scale(SparseVector<KeyType, ValueType>*, const ScaleType&);

// ScaleInto(u,v,c) : u <- v * c
template <class KeyType, class ValueType, class ScaleType>
void ScaleInto(SparseVector<KeyType, ValueType>* u,
               const SparseVector<KeyType, ValueType>& v,
               const ScaleType& c);

// AddScaled(u,v,c) : u <- u + v * c
template <class KeyType, class ValueType, class ScaleType>
void AddScaled(SparseVector<KeyType, ValueType>* u,
               const SparseVector<KeyType, ValueType>& v,
               const ScaleType& c);

// AddScaledInto(w,u,v,c) : w <- u + v * c
template <class KeyType, class ValueType, class ScaleType>
void AddScaledInto(SparseVector<KeyType, ValueType>* w,
                   const SparseVector<KeyType, ValueType>& u,
                   const SparseVector<KeyType, ValueType>& v,
                   const ScaleType& c);

// DotProduct(u, v) : r <- dot(u,v)
template <class KeyType, class ValueType>
ValueType DotProduct(const SparseVector<KeyType, ValueType>& v1,
                     const SparseVector<KeyType, ValueType>& v2);

// Output a sparse vector in human readable format.
template <class KeyType, class ValueType>
ostream& operator<<(ostream& output,
                    const SparseVector<KeyType, ValueType>& vec);


} // namespace brook
 
#endif // IN_MEMORY_STORE_SPARSE_VECTOR_H_
