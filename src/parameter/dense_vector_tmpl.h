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
class DenseVectorTmpl : public vector<ValueType> {
public:
    typedef typename vector<ValueType>::const_iterator const_iterator;
    typedef typename vector<ValueType>::iterator iterator;

    DenseVectorTmpl(size_t size, const ValueType& init)
    : vector<ValueType>(size, init) {}

    DenseVectorTmpl()
    : vector<ValueType>() {}

    void Add(const DenseVectorTmpl<ValueType>&);

    void Minus(const DenseVectorTmpl<ValueType>&);

    void Scale(const ValueType&);

    void ScaleInto(const DenseVectorTmpl<ValueType>&,
                   const ValueType&);

    void AddScaled(const DenseVectorTmpl<ValueType>&,
                   const ValueType&);

    void AddScaledInto(const DenseVectorTmpl<ValueType>&,
                       const DenseVectorTmpl<ValueType>&,
                       const ValueType&);

    ValueType DotProduct(const DenseVectorTmpl<ValueType>&);
};

// Add(v) : this <- this + v
template<class ValueType>
void DenseVectorTmpl<ValueType>::Add(const DenseVectorTmpl<ValueType>& v) {
    size_t len = this->size();
    CHECK_EQ(len, v.size());
    for (size_t i = 0 ; i < len ; ++i) {
        (*this)[i] += v[i];
    }
}

// Minus(v) : this <- this - v    
template<class ValueType>
void DenseVectorTmpl<ValueType>::Minus(const DenseVectorTmpl<ValueType>& v) {
    size_t len = this->size();
    CHECK_EQ(len, v.size());
    for (size_t i = 0 ; i < len ; ++i) {
        (*this)[i] -= v[i];
    }
}

// Scale(c) : this <- this * c
template<class ValueType> 
void DenseVectorTmpl<ValueType>::Scale(const ValueType& c) {
    size_t len = this->size();
    for (size_t i = 0 ; i < len ; ++i) {
        (*this)[i] *= c;
    }
}

// ScaleInto(v, c) : this <- v * c
template<class ValueType> 
void DenseVectorTmpl<ValueType>::ScaleInto(const DenseVectorTmpl<ValueType>& v,
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
void DenseVectorTmpl<ValueType>::AddScaled(const DenseVectorTmpl<ValueType>& v,
                                           const ValueType& c) {
    int len = this->size();
    CHECK_EQ(len, v.size());
    CHECK_LT(0, len);
    for (size_t i = 0 ; i < len ; ++i) {
        (*this)[i] += v[i] * c;
    }
}

// AddScaledInto(u, v, c) : this <- u + v * c
template<class ValueType>
void DenseVectorTmpl<ValueType>::AddScaledInto(const DenseVectorTmpl<ValueType>& u,
                                               const DenseVectorTmpl<ValueType>& v,
                                               const ValueType& c) {
    int len = this->size();
    CHECK_EQ(len, u.size());
    CHECK_EQ(len, v.size());
    CHECK_LT(0, len);
    for (size_t i = 0 ; i < len ; ++i) {
        (*this)[i] = u[i] + v[i] * c;
    }
}

// DotProduct(v) : this <- dot(this, v)
template<class ValueType>
ValueType DenseVectorTmpl<ValueType>::DotProduct(const DenseVectorTmpl<ValueType>& v) 
{
    int len = this->size();
    CHECK_EQ(len, v.size());
    ValueType ret = 0;
    for (size_t i = 0 ; i < len ; ++i) {
        ret += (*this)[i] * v[i];
    }
    return ret;
}

} // namespace brook

#endif // PARAMETER_DENSE_VECTOR_TMPI_H_
