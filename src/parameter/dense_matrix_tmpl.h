// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
// Define the class template DenseMatrixImpl and operations required by
// users.
//
#ifndef PARAMETER_DENSE_MATRIX_TMPL_H_
#define PARAMETER_DENSE_MATRIX_TMPL_H_

#include "src/dense_vector_tmpl.h"

#include <vector>

namespace brook {

using std::vector;

template<class ValueType>
class DenseMatrixImpl {
public:
    typedef DenseVectorImpl<ValueType> DV;

    DenseMatrixImpl(size_t row_size, size_t col_size, const ValueType& init)
    : vector<DV>(row_size, DV(col_size, init)) {}

    DenseMatrixImpl()
    : vector<DV>() {}

    void Add(const DenseMatrixImpl<ValueType>&);

    void Minus(const DenseMatrixImpl<ValueType>&);

    void Scale(const ValueType&);

    void ScaleInto(const DenseMatrixImpl<ValueType>&,
                   const ValueType&);

    void AddScaled(const DenseMatrixImpl<ValueType>&,
                   const ValueType&);

    void AddScaledInto(const DenseMatrixImpl<ValueType>&,
                       const DenseMatrixImpl<ValueType>&,
                       const ValueType&);

    size_t RowSize() { return matrix_.size(); }
   
    const DV& operator[](size_t i) const {
        CHECK_LE(0, i);
        CHECK_LT(i, matrix_.size());
        return matrix_[i];
    }

protected:
    vector<DV> matrix_;
};

// Add(v) : this <- this + v
template<class ValueType>
void DenseMatrixImpl<ValueType>::Add(const DenseMatrixImpl<ValueType>& v) {
    size_t row_size = this->RowSize();
    CHECK_EQ(row_size, v.RowSize());
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].Add(v[row]);
    }
}

// Minus(v) : this <- this - v
template<class ValueType>
void DenseMatrixImpl<ValueType>::Minus(const DenseMatrixImpl<ValueType>& v) {
    size_t row_size = this->RowSize();
    CHECK_EQ(row_size, v.size());
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].Minus(v[row]);
    }
}

// Scale(c) : this <- this * c
template<class ValueType>
void DenseMatrixImpl<ValueType>::Scale(const ValueType& c) {
    size_t row_size = this->RowSize();
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].Scale(c);
    }
}

// ScaleInto(v, c) : this <- v * c
template<class ValueType>
void DenseMatrixImpl<ValueType>::ScaleInto(const DenseMatrixImpl<ValueType>& v,
                                           const ValueType& c) {
    size_t row_size = this->RowSize();
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].ScaleInto(v[row], c);
    }
}

// AddScaled(v, c) : this <- this + v * c
template<class ValueType>
void DenseMatrixImpl<ValueType>::AddScaled(const DenseMatrixImpl<ValueType>& v,
                                           const ValueType& c) {
    size_t row_size = this->RowSize();
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].AddScaled(v[row], c);
    }
}

// AddScaledInto(u,v,c) : this <- u + v * c
template<class ValueType>
void DenseMatrixImpl<ValueType>::AddScaledInto(const DenseMatrixImpl<ValueType>& u,
                                               const DenseMatrixImpl<ValueType>& v,
                                               const ValueType& c)
{
    size_t row_size = this->RowSize();
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].AddScaled(u[row], v[row], c);
    }
}

} // namespace brook

#endif // PARAMETER_DENSE_MATRIX_TMPL_H_
