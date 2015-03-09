// Copyright :  2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
// Define the class template SparseTableTmpl and operations
// required by users
//
#ifndef IN_MEMORY_STORE_SPARSE_TABLE_H_
#define IN_MEMORY_STORE_SPARSE_TABLE_H_

#include <vector>

#include "src/in_memory_store/sparse_vector.h"


namespace brook {

using std::vector;

template <class KeyType, class ValueType>
class SparseTableTmpl {
public:
    typedef vector<SparseVectorTmpl<KeyType, ValueType> > SparseTable;
    SparseTableTmpl(size_t size, size_t len, const ValueType& init) 
        : ST(size)
    {
        for (int i = 0 ; i < size ; i++) {
            ST[i].resize(len, init);
        }
    }


protected:
    SparseTable ST;
};

} // namespace brook

#endif // IN_MEMORY_STORE_SPARSE_TABLE_H_
