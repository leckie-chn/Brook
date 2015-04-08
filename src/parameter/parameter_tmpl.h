// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
// Parameter is an important class which been used in server.
//
#ifndef PARAMETER_PARAMETER_TMPL_H_
#define PARAMETER_PARAMETER_TMPL_H_

#include "src/parameter/dense_vector_tmpl.h"

#include "src/util/bitmap.h"

#include <vector>


namespace brook {

template <class ValueType>
class Parameter {

typedef DenseVectorImpl<ValueType> DenseVector;
typedef DenseMatrixImpl<ValueType> DenseMatrix;

public:

private:
    DenseVector parameter_;
    std::vector<Bitmap> agent_page_;
    std::vector<int> update_count_;
    DenseMatrix version_update_;
};
 // namespace brook

#endif // PARAMETER_PARAMETER_TMPL_H_
