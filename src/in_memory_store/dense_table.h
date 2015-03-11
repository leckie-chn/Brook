// Copyright : 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
// Define the class template DenseTableTmpl and operations
// required by users.
//
#ifndef IN_MEMORY_STORE_DENSE_TABLE_H_
#define IN_MEMORY_STORE_DENSE_TABLE_H_

#include <vector>

#include "src/base/common.h"
#include "src/in_memory_store/dense_vector.h"

namespace brook {

using std::vector;

template <class ValueType>
class DenseTableTmpl {
public:
    typedef vector<DenseVectorTmpl<ValueType> > DenseTable;
    typedef DenseVectorTmpl<ValueType> DV;

    DenseTableTmpl() {}

    DenseTableTmpl(size_t size) : DT(size) {}
    ~DenseTableTmpl() {}

    DV& operator[] (size_t index) {
        CHECK_GE(index, 0);
        CHECK_LT(index, DT.size());
        return DT[index];
    }

    void set(const size_t index, const DV& dv) {
        CHECK_GE(index, 0);
        CHECK_LT(index, DT.size());
        DT[index] = dv;
    }

    void push_back(const DV& dv) {
        DT.push_back(dv);
    }

    size_t size() const {
        return DT.size();
    }

private:
    DenseTable DT;

};

// TableScale(v, c) : v <- v * c
template <class ValueType, class ScaleType>
void TableScale(DenseTableTmpl<ValueType>& v,
                const ScaleType& c)
{
    for (size_t i = 0 ; i < v.size() ; i++) {
        Scale(v[i], c);
    }
}

// TableScaleInto(u, v, c) : u <- v * c
template <class ValueType, class ScaleType>
void TableScaleInto(DenseTableTmpl<ValueType>& u,
                    DenseTableTmpl<ValueType>& v,
                    const ScaleType& c)
{
    for (size_t i = 0 ; i < v.size() ; i++) {
        ScaleInto(v[i], u[i], c);
    }
}

// TableAddScale(u, v, c) : u <- u + v * c
template <class ValueType, class ScaleType>
void TableAddScale(DenseVectorTmpl<ValueType>& u,
                   DenseVectorTmpl<ValueType>& v,
                   const ScaleType& c)
{
    for (size_t i = 0 ; i < v.size() ; i++) {
        AddScaled(u[i], v[i], c);
    }
}

// TableAddScaleInto(w, u, v, c) : w <- u + v * c
template <class Value, class ScaleType>
void TableAddScaleInto(DenseVectorTmpl<ValueType>& w,
                       DenseVectorTmpl<ValueType>& u,
                       DenseVectorTmpl<ValueType>& v,
                       const ScaleType& c)
{
    for (size_t i = 0 ; i < v.size() ; i++) {
        AddScaledInto(w[i], u[i], v[i], c);
    }
}

// Output a sparse table in human readable format.
template <class ValueType>
ostream& operator<<(ostream& output,
                    const DenseVectorTmpl<ValueType>& table)
{
    for (size_t i = 0 ; i < table.size() ; i++) {
        output << table[i] << "\n";
    }
}

} // namespace brook

#endif // IN_MEMORY_STORE_DENSE_TABLE_H_
