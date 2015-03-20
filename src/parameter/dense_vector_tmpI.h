// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
// Define the class template DenseVectorImpl and operations required by 
// users.
//
#ifndef PARAMETER_DENSE_VECTOR_TMPI_H_
#define PARAMETER_DENSE_VECTOR_TMPI_H_

#include <vector>

namespace brook {

using std::ostream
using std::vector

template<class Value>
class DenseVectorImpl : public vector<ValueType> {
public:
    typedef typename vector<ValueType>::const_iterator const_iterator;
    typedef typename vector<ValueType>::iterator iterator;
}

} // namespace brook

#endif // PARAMETER_DENSE_VECTOR_TMPI_H_
