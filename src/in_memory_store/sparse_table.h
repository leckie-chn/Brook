// Copyright :  2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
// Define the class template SparseTableTmpl and operations
// required by users
//
#ifndef IN_MEMORY_STORE_SPARSE_TABLE_H_
#define IN_MEMORY_STORE_SPARSE_TABLE_H_

#include <vector>

#include "src/base/common.h"
#include "src/in_memory_store/sparse_vector.h"

namespace brook {

using std::vector;

template <class KeyType, class ValueType>
class SparseTableTmpl {
public:
    typedef vector<SparseVectorTmpl<KeyType, ValueType> > SparseTable;
    typedef SparseVectorTmpl<KeyType, ValueType> SV;

    SparseTableTmpl(size_t size) : ST(size) {}
    ~SparseTableTmpl() {}

    // We constrain operator [] a read-only operation to prevent
    // accidential insert of elements.
    const SV& operator[] (size_t index) const {
        CHECK_GE(index, 0);
        CHECK_LT(index, ST.size());
        return ST[index];
    }

    void set(const size_t index, const SV& sv) {
        CHECK_GE(index, 0);
        CHECK_LT(index, ST.size());
        ST[index] = sv;
    }

    size_t size() const {
        return ST.size();
    }

protected:
    SparseTable ST;
};

// TableScale(v, c) : v <- v * c
template <class KeyType, class ValueType, class ScaleType>
void TableScale(SparseTableTmpl<KeyType, ValueType>* v,
           const ValueType& c)
{
    for (size_t i = 0 ; i < v->size() ; i++) {
        Scale(v[i], c);
    }
}



} // namespace brook

#endif // IN_MEMORY_STORE_SPARSE_TABLE_H_
