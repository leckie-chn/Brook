// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
// Define the class template DenseMatrixImpl and operations required by
// users.
//
#ifndef PARAMETER_DENSE_MATRIX_TMPL_H_
#define PARAMETER_DENSE_MATRIX_TMPL_H_

#include "src/parameter/dense_vector_tmpl.h"

#include <vector>

namespace brook {

using std::vector;

template<class ValueType>
class DenseMatrixTmpl {
public:
    typedef DenseVectorTmpl<ValueType> DV;

    DenseMatrixTmpl(size_t row_size, size_t col_size, const ValueType& init)
    : matrix_(row_size, DV(col_size, init)) {}

    DenseMatrixTmpl()
    : matrix_() {}

    void Set(size_t i, DenseVectorTmpl<ValueType>& v) {
        CHECK_LE(0, i);
        CHECK_LT(i, matrix_.size());
        matrix_[i] = v;
    }

    void Push_back(DenseVectorTmpl<ValueType>& v) {
        matrix_.push_back(v);
    }

    void Add(DenseMatrixTmpl<ValueType>&);

    void Minus(DenseMatrixTmpl<ValueType>&);

    void Scale(const ValueType&);

    void ScaleInto(DenseMatrixTmpl<ValueType>&,
                   const ValueType&);

    void AddScaled(DenseMatrixTmpl<ValueType>&,
                   const ValueType&);

    void AddScaledInto(DenseMatrixTmpl<ValueType>&,
                       DenseMatrixTmpl<ValueType>&,
                       const ValueType&);

    size_t RowSize() { return matrix_.size(); }
   
    DV& operator[](size_t i) {
        CHECK_LE(0, i);
        CHECK_LT(i, matrix_.size());
        return matrix_[i];
    }

protected:
    vector<DV> matrix_;
};

// Add(v) : this <- this + v
template<class ValueType>
void DenseMatrixTmpl<ValueType>::Add(DenseMatrixTmpl<ValueType>& v) {
    size_t row_size = this->RowSize();
    CHECK_EQ(row_size, v.RowSize())
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].Add(v[row]);
    }
}

// Minus(v) : this <- this - v
template<class ValueType>
void DenseMatrixTmpl<ValueType>::Minus(DenseMatrixTmpl<ValueType>& v) {
    size_t row_size = this->RowSize();
    CHECK_EQ(row_size, v.RowSize());
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].Minus(v[row]);
    }
}

// Scale(c) : this <- this * c
template<class ValueType>
void DenseMatrixTmpl<ValueType>::Scale(const ValueType& c) {
    size_t row_size = this->RowSize();
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].Scale(c);
    }
}

// ScaleInto(v, c) : this <- v * c
template<class ValueType>
void DenseMatrixTmpl<ValueType>::ScaleInto(DenseMatrixTmpl<ValueType>& v,
                                           const ValueType& c) {
    size_t row_size = this->RowSize();
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].ScaleInto(v[row], c);
    }
}

// AddScaled(v, c) : this <- this + v * c
template<class ValueType>
void DenseMatrixTmpl<ValueType>::AddScaled(DenseMatrixTmpl<ValueType>& v,
                                           const ValueType& c) {
    size_t row_size = this->RowSize();
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].AddScaled(v[row], c);
    }
}

// AddScaledInto(u,v,c) : this <- u + v * c
template<class ValueType>
void DenseMatrixTmpl<ValueType>::AddScaledInto(DenseMatrixTmpl<ValueType>& u,
                                               DenseMatrixTmpl<ValueType>& v,
                                               const ValueType& c)
{
    size_t row_size = this->RowSize();
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].AddScaledInto(u[row], v[row], c);
    }
}

} // namespace brook

#endif // PARAMETER_DENSE_MATRIX_TMPL_H_
