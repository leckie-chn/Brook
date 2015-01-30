// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#include "src/in_memory_store/sparse_vector.h"

namespace brook {

template<class K, class V>
const V& SparseVector<K, V>::operator[] (const K& key) const {
    const_iterator iter = this->find(key);
    if (iter == this->end()) {
        return zero_;
    }
    return iter->second;
}

template<class K, class V>
void SparseVector<K, V>::set(const K& key, const V& value) {
    iterator iter = this->find(key);
    if (iter != this->end()) {
        if (IsZero(value)) {
            this->erase(iter);
        } else {
            iter->second = value;
        }
    } else {
        if (!IsZero(value)) {
            this->insert(pair<K, V>(key, value));
        }
    }
}

template<class K, class V>
bool SparseVector<K, V>::has(const K& key) const {
    return this->find(key) != this->end();
}

// Scale(v, c) : v <- v * c
template <class K, class V, class S>
void Scale(SparseVector<K, V>* v, const S& c) {
    typedef SparseVector<K, V> SV;
    for (typename SV::iterator i = v->begin() ; i != v->end(); ++i) {
        i->second *= c;
    }
}

// ScaleInto(u, v, c) : u <- v * c
template <class K, class V, class S>
void ScaleInto(SparseVector<K, V>* u,
               const SparseVector<K, V>& v,
               const S& c)
{
    typedef SparseVector<K, V> SV;
    u->clear();
    for (typename SV::const_iterator i = v.begin() ; i != v.end(); ++i) {
        u->set(i->first, i->second * c);
    }
}

// AddScaleInto(w, u, v, c) : w <- u + v * c
template <class K, class V, class S>
void AddScaleInto(SparseVector<K, V>* w,
                  const SparseVector<K, V>& u,
                  const SparseVector<K, V>& v,
                  const S& c)
{
    typedef SparseVector<K, V> SV;
    w->clear();
    typename SV::const_iterator i = u.begin();
    typename SV::const_iterator j = v.begin();
    while (i != u.end() && j != v.end()) {
        if (i->first == j->first) {
            w->set(i->first, i->second + j->second * c);
            ++i;
            ++j;
        } else if (i->first < j->first) {
            w->set(i->first, i->second);
            ++i;
        } else {
            w->set(i->first, i->second);
            ++j;
        }
    }
    while (i != u.end()) {
        w->set(i->first, i->second);
        ++i;
    }
    while (j != v.end()) {
        w->set(j->first, j->second * c);
        ++j;
    }
}



} // namespace brook
