// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
// Define the class template SparseMatrixImpl and operations required by
// users.
//
#ifndef PARAMETER_SPARSE_MATRIX_TMPL_H_
#define PARAMETER_SPARSE_MATRIX_TMPL_H_

#include "src/parameter/sparse_vector_tmpl.h"

#include "src/util/common.h"

#include <vector>

namespace brook {

using std::vector;

template<class KeyType, class ValueType>
class SparseMatrixTmpl {
public:
    typedef SparseVectorTmpl<KeyType, ValueType> SV;

    SparseMatrixTmpl(size_t row_size)
    : matrix_(row_size) {}

    SparseMatrixTmpl()
    : matrix_() {}

    void Set(size_t i, SparseVectorTmpl<KeyType, ValueType>& v) {
        CHECK_LE(0, i);
        CHECK_LT(i, matrix_.size());
        matrix_[i] = v;
    }

    void Push_back(SparseVectorTmpl<KeyType, ValueType>& v) {
        matrix_.push_back(v);
    }

    void Add(SparseMatrixTmpl<KeyType, ValueType>&);

    void Minus(SparseMatrixTmpl<KeyType, ValueType>&);

    void Scale(const ValueType&);

    void ScaleInto(SparseMatrixTmpl<KeyType, ValueType>&,
                   const ValueType&);

    void AddScaled(SparseMatrixTmpl<KeyType, ValueType>&,
                   const ValueType&);

    void AddScaledInto(SparseMatrixTmpl<KeyType, ValueType>&,
                       SparseMatrixTmpl<KeyType, ValueType>&,
                       const ValueType&);

    size_t RowSize() { return matrix_.size(); }

    SV& operator[](size_t i) {
        CHECK_LE(0, i);
        CHECK_LT(i, matrix_.size());
        return matrix_[i];
    }

protected:
    vector<SV> matrix_;
};

// Add(v) : this <- this + v
template<class KeyType, class ValueType>
void SparseMatrixTmpl<KeyType, ValueType>::Add(SparseMatrixTmpl<KeyType, ValueType>& v) {
    size_t row_size = this->RowSize();
    CHECK_EQ(row_size, v.RowSize());
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].Add(v[row]);
    }
}

// Minus(v) : this <- this - v
template<class KeyType, class ValueType>
void SparseMatrixTmpl<KeyType, ValueType>::Minus(SparseMatrixTmpl<KeyType, ValueType>& v) {
    size_t row_size = this->RowSize();
    CHECK_EQ(row_size, v.RowSize());
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].Minus(v[row]);
    }
}

// Scale(c) : this <- this * c
template<class KeyType, class ValueType>
void SparseMatrixTmpl<KeyType, ValueType>::Scale(const ValueType& c) {
    size_t row_size = this->RowSize();
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].Scale(c);
    }
}

// ScaleInto(v, c) : this <- v * c
template<class KeyType, class ValueType>
void SparseMatrixTmpl<KeyType, ValueType>::ScaleInto(SparseMatrixTmpl<KeyType, ValueType>& v,
                                                     const ValueType& c) {
    size_t row_size = this->RowSize();
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].ScaleInto(v[row], c);
    }
}

// AddScaled(v, c) : this <- this + v * c
template<class KeyType, class ValueType>
void SparseMatrixTmpl<KeyType, ValueType>::AddScaled(SparseMatrixTmpl<KeyType, ValueType>& v,
                                                     const ValueType& c) {
    size_t row_size = this->RowSize();
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].AddScaled(v[row], c);
    }
}

// AddScaledInto(u,v,c) : this <- u + v * c
template<class KeyType, class ValueType>
void SparseMatrixTmpl<KeyType, ValueType>::AddScaledInto(SparseMatrixTmpl<KeyType, ValueType>& u,
                                                         SparseMatrixTmpl<KeyType, ValueType>& v,
                                                         const ValueType& c)
{
    size_t row_size = this->RowSize();
    for (size_t row = 0 ; row < row_size ; ++row) {
        (*this)[row].AddScaledInto(u[row], v[row], c);
    }
}

} // brook

#endif // PARAMETER_SPARSE_MATRIX_TMPL_H_
