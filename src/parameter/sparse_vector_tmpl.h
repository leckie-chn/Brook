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


// We use std::map as the container of a sparse vector. Because
// std::map implements a sorting tree (RB-tree), so its iterator
// accesses elements in known order of keys. This is important for
// sparse vector operations like dot-product and add-multi-into.
// The ValueType must be a numberical type supporting const 0.
template<class KeyType, class ValueType>
class SparseVectorTmpl : public map<KeyType, ValueType> {
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
            if (!IsZero(value)) {
                this->insert(pair<KeyType, ValueType>(key, value));
            }
        }
    }

    bool has(const KeyType& key) const {
        return this->find(key) != this->end();
    }

    void Add(const SparseVectorTmpl<KeyType, ValueType>&);

    void Minus(const SparseVectorTmpl<KeyType, ValueType>&);

    void Scale(const ValueType&);

    void ScaleInto(const SparseVectorTmpl<KeyType, ValueType>&,
                   const ValueType&);

    void AddScaled(const SparseVectorTmpl<KeyType, ValueType>&,
                   const ValueType&);

    void AddScaledInto(const SparseVectorTmpl<KeyType, ValueType>&,
                       const SparseVectorTmpl<KeyType, ValueType>&,
                       const ValueType&);
    
    ValueType DotProduct(const SparseVectorTmpl<KeyType, ValueType>&);

protected:
    static const ValueType zero_;

    static bool IsZero(const ValueType& value) {
        return value == 0;
    }
};

template<class KeyType, class ValueType>
const ValueType SparseVectorTmpl<KeyType, ValueType>::zero_(0);

// Add(v) : this <- this + v
template<class KeyType, class ValueType>
void SparseVectorTmpl<KeyType, ValueType>::Add(const SparseVectorTmpl<KeyType, ValueType>& v) {
    typedef SparseVectorTmpl<KeyType, ValueType> SV;
    for (typename SV::const_iterator i = v.begin() ; i != v.end() ; ++i) {
        this->set(i->first, (*this)[i->first] + i->second);
    }
}

// Minus(v) : this <- this - v
template<class KeyType, class ValueType>
void SparseVectorTmpl<KeyType, ValueType>::Minus(const SparseVectorTmpl<KeyType, ValueType>& v) {
    typedef SparseVectorTmpl<KeyType, ValueType> SV;
    for (typename SV::const_iterator i = v.begin() ; i != v.end() ; ++i) {
        this->set(i->first, (*this)[i->first] - i->second);
    }

}

// Scale(c) : this <- this * c
template<class KeyType, class ValueType>
void SparseVectorTmpl<KeyType, ValueType>::Scale(const ValueType& c) {
    typedef SparseVectorTmpl<KeyType, ValueType> SV;
    for (typename SV::iterator i = this->begin() ; i != this->end() ; ++i) {
        i->second *= c;
    }
}

// ScaleInto(v, c) : this <- v * c
template<class KeyType, class ValueType>
void SparseVectorTmpl<KeyType, ValueType>::ScaleInto(const SparseVectorTmpl<KeyType, ValueType>& v,
                                                      const ValueType& c) {
    typedef SparseVectorTmpl<KeyType, ValueType> SV;
    this->clear();
    for (typename SV::const_iterator i = v.begin() ; i != v.end() ; ++i) {
        this->set(i->first, i->second * c);
    }
}

// AddScaled(v, c) : this <- this + v * c
template<class KeyType, class ValueType>
void SparseVectorTmpl<KeyType, ValueType>::AddScaled(const SparseVectorTmpl<KeyType, ValueType>& v,
                                                     const ValueType& c) {
    typedef SparseVectorTmpl<KeyType, ValueType> SV;
    for (typename SV::const_iterator i = v.begin() ; i != v.end(); ++i) {
        this->set(i->first, (*this)[i->first] + i->second * c);
    }
}

// AddScaledInto(u,v,c) : this <- u + v * c
template<class KeyType, class ValueType>
void SparseVectorTmpl<KeyType, ValueType>::AddScaledInto(const SparseVectorTmpl<KeyType, ValueType>& u,
                                                         const SparseVectorTmpl<KeyType, ValueType>& v,
                                                         const ValueType& c) {
    typedef SparseVectorTmpl<KeyType, ValueType> SV;
    this->clear();
    typename SV::const_iterator i = u.begin();
    typename SV::const_iterator j = v.begin();
    while (i != u.end() && j != v.end()) {
        if (i->first == j->first) {
            this->set(i->first, i->second + j->second * c);
            ++i;
            ++j;
        } else if (i->first < j->first) {
            this->set(i->first, i->second);
            ++i;
        } else {
            this->set(j->first, j->second * c);
            ++j;
        }
    }
    while (i != u.end()) {
        this->set(i->first, i->second);
        ++i;
    }
    while (j != v.end()) {
        this->set(j->first, j->second * c);
        ++j;
    }
}

// DotProduct(v) : r <- this * v
template<class KeyType, class ValueType>
ValueType SparseVectorTmpl<KeyType, ValueType>::DotProduct(const SparseVectorTmpl<KeyType, ValueType>& v) {
    typedef SparseVectorTmpl<KeyType, ValueType> SV;
    typename SV::const_iterator i = v.begin();
    typename SV::const_iterator j = this->begin();
    ValueType ret = 0;
    while (i != v.end() && j != this->end()) {
        if (i->first == j->first) {
            ret += i->second * j->second;
            ++i;
            ++j;
        } else if (i->first < j->first) {
            ++i;
        } else {
            ++j;
        }
    }
    return ret;
}

} // namespace


#endif // PARAMETER_SPARSE_VECTOR_TMPL_H_
