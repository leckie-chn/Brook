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
    typedef typename DenseVectorImpl<ValueType> DV;

    DenseMatrixImpl(size_t row_size, size_t col_size, const ValueType& init)
    : vector<DV>(row_size, DV(col_size, init)) {}

    DenseMatrixImpl()
    : vector<DV>() {}

    void Scale(const ValueType&);

    void ScaleInto(const DenseMatrixImpl<ValueType>&,
                   const ValueType&);

    void AddScaled(const DenseMatrixImpl<ValueType>&,
                   const ValueType&);

    void AddScaledInto(const DenseMatrixImpl<ValueType>&,
                       const DenseMatrixImpl<ValueType>&,
                       const ValueType&);

protected:
    vector<DV> matrix_;
};

} // namespace brook

#endif // PARAMETER_DENSE_MATRIX_TMPL_H_
