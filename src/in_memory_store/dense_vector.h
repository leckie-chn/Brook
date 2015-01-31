// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef IN_MEMORY_STORE_DENSE_VECTOR_H_
#define IN_MEMORY_STORE_DENSE_VECTOR_H_

#include <vector>

namespace brook {

using std::ostream;
using std::vector;

template <class ValueType>
class DenseVector : public vector<ValueType> {
public:
    typedef typename vector<ValueType>::const_iterator const_iterator;
    typedef typename vector<ValueType>::iterator iterator;

    DenseVector(size_t size, const ValueType& init) 
       : vector<ValueType>(size, init) {}
    
    DenseVector() 
       : vector<ValueType>() {}
};

// Add(v, u) : v <- v + u
template <class ValueType>
void Add(DenseVector<ValueType>*v, DenseVector<ValueType>& u) {
    CHECK_EQ(v->size(), u.size());
    for (size_t i = 0 ; i < v->size() ; ++i) {
        (*v)[i] += u[i];
    }
}

// Minus(v, u) : v <- v - u
template <class ValueType>
void Minus(DenseVector<ValueType>* v, DenseVector<ValueType>& u) {
    CHECK_EQ(v->size(), u.size());
    for (size_t i = 0 ; i < v->size(); ++i) {
        (*v)[i] -= u[i];
    }
}

// Scale(v, c) : v <- v * c
template <class ValueType, class ScaleType>
void Scale(DenseVector<ValueType>* v,
           const ScaleType& c) 
{
    for (size_t i = 0; i < v->size(); ++i) {
        (*v)[i] *= c;
    }
}

// ScaleInto(u, v, c) : u <- v * c
template <class ValueType, class ScaleType>
void ScaleInto(DenseVector<ValueType>* u,
               const DenseVector<ValueType>& v,
               const ScaleType& c)
{
    CHECK_EQ(v.size(), u->size());
    CHECK_LT(0, v.size());
    for (size_t i = 0 ; i < v.size(); ++i) {
        (*u)[i] = v[i] * c;
    }
}

// AddScaled(u,v,c) : u <- u + v * c
template <class ValueType, class ScaleType>
void AddScaled(DenseVector<ValueType>* u,
               const DenseVector<ValueType>& v,
               const ScaleType& c)
{
    CHECK_EQ(v.size(), u->size());
    CHECK_LT(0, v.size());
    for (size_t i = 0 ; i < v.size(); ++i) {
        (*u)[i] += v[i] * c;
    }
}

// AddScaledInto(w, u, v, c) : w <- u + v * c
template <class ValueType, class ScaleType>
void AddScaledInto(DenseVector<ValueType>* w,
                   const DenseVector<ValueType>& u,
                   const DenseVector<ValueType>& v,
                   const ScaleType& c)
{
    CHECK_EQ(u.size(), v.size());
    CHECK_EQ(u.size(), w->size());
    for (size_t i = 0 ; i < u.size(); ++i) {
        (*w)[i] = u[i] + v[i] * c;
    }
}

// DotProduct(u, v) : r <- dot(u, v)
template <class ValueType>
ValueType DotProduct(const DenseVector<ValueType>& v1,
                     const DenseVector<ValueType>& v2)
{
    CHECK_EQ(v1.size(), v2.size());
    ValueType ret = 0;
    for (size_t i = 0; i < v1.size(); ++i) {
        ret += v1[i] * v2[i];
    }
    return ret;
}

// Ouput a dense vector in humman readable format.
template<class ValueType>
ostream& operator<< (ostream& output,
                     const DenseVector<ValueType>& vec)
{
    output << " [ ";
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] != 0) // to keep the format the same with sparse vector.
        {
            output << i << ":" << vec[i] << " ";
        }    
    }
    output << "]";
    return output;
}


} // namespace brook

#endif // IN_MEMORY_STORE_DENSE_VECTOR_H_
