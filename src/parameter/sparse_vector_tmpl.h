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
public:
    typedef typename map<KeyType, ValueType>::const_iterator const_iterator;
    typedef typename map<KeyType, ValueType>::iterator iterator;

    // We constrain operator[] a read-only operation to prevent
    // accidential insert of elements.
    const ValueType& operator[](const KeyType& key) const {
        const_iterator iter = this->find(key);
        if (iter == this->end()) {
            return zero_;
        }
        return iter->second;
    }

    // Set a value at given key. If value == 0, an existing key-value
    // pair is removed. If value != 0, the value is set or inserted.
    // This function alse serves as a convenient from of insert(),
    // no need to use std::pair;
    void set(const KeyType& key, const ValueType& value) {
        iterator iter = this->find(key);
        if (iter != this->end()) {
            if (IsZero(value)) {
                this->erase(iter);
            } else {
                iter->second = value;
            }
        } else {
            if (!IsZero()) {
                this->insert(pair<KeyType, ValueType>(key, value));
            }
        }
    }

    bool has(const KeyType& key) const {
        return this->find(key) != this->end();
    }

protected:


};

} // namespace


#endif // PARAMETER_SPARSE_VECTOR_TMPL_H_
