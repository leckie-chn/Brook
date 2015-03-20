// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
// Define the class template DenseVectorImpl and operations required by 
// users.
//
#ifndef PARAMETER_DENSE_VECTOR_TMPI_H_
#define PARAMETER_DENSE_VECTOR_TMPI_H_

#include <vector>

#include "src/util/common.h"

namespace brook {

using std::ostream;
using std::vector;

template<class ValueType>
class DenseVectorImpl : public vector<ValueType> {
public:
    typedef typename vector<ValueType>::const_iterator const_iterator;
    typedef typename vector<ValueType>::iterator iterator;

    DenseVectorImpl(size_t size, const ValueType& init)
    : vector<ValueType>(size, init) {}

    DenseVectorImpl()
    : vector<ValueType>() {}

    void Scale(const ValueType&);

    void ScaleInto(const DenseVectorImpl<ValueType>&,
                   const ValueType&);

    void AddScaled(const DenseVectorImpl<ValueType>& v,
                   const ValueType&);
};

// Scale(c) : this <- this * c
template<class ValueType> 
void DenseVectorImpl<ValueType>::Scale(const ValueType& c) {
    size_t len = this->size();
    for (size_t i = 0 ; i < len ; ++i) {
        (*this)[i] *= c;
    }
}

// ScaleInto(v, c) : this <- v * c
template<class ValueType> 
void DenseVectorImpl<ValueType>::ScaleInto(const DenseVectorImpl<ValueType>& v,
                                           const ValueType& c) {
    size_t len = this->size();
    CHECK_EQ(len, v.size());
    CHECK_LT(0, len);
    for (size_t i = 0 ; i < len ; ++i) {
        (*this)[i] = v[i] * c;
    }
}

// AddScaled(v, c) : this <- this + v * c
template<class ValueType>
void DenseVectorImpl<ValueType>::AddScaled(const DenseVectorImpl<ValueType>& v,
                                           const ValueType& c) {
    int len = this->size();
    CHECK_EQ(len, v.size());
    CHECK_LT(0, len);
    for (size_t i = 0 ; i < len ; ++i) {
        (*this)[i] += v[i] * c;
    }
}


} // namespace brook

#endif // PARAMETER_DENSE_VECTOR_TMPI_H_
