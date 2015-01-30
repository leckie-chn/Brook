// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#include "src/in_memory_store/sparse_vector.h"

namespace brook {

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

// DotProduct(u, v) : r <- dot(u, v)
template <class K, class V>
V DotProduct(const SparseVector<K, V>& v1,
             const SparseVector<K, V>& v2)
{
    typedef SparseVector<K, V> SV;
    typename SV::const_iterator i = v1.begin();
    typename SV::const_iterator j = v2.begin();
    V ret = 0;
    while (i != v1.end() && j != v2.end()) {
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

// Output a sparse vector in human readable format.
template<class K, class V>
ostream& operator<<(ostream& output,
                    const SparseVector<K, V>& vec)
{
    typedef SparseVector<K, V> SV;
    output << " [ ";
    for (typename SV::const_iterator i = vec.begin(); i != vec.end(); ++i) {
        output << i->first << ":" << i->second << " ";
    }
    output << "]";
    return output;
}

} // namespace brook
