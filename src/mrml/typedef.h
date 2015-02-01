// Coptirght 2015 PKU-Cloud.
// Author :  Chao Ma (mctt90@gmail.com)
//
#ifndef MRML_TYPEDEF_H_
#define MRML_TYPEDEF_H_

#include "src/in_memory_store/sparse_vector.h"
#include "src/in_memory_store/dense_vector.h"

namespace brook {

using std::string;

typedef SparseVector<string, float> RealVector;

} // namespace brook


#endif // MRML_TYPEDEF_H_
