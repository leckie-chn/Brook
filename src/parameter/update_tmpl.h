// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef PARAMETER_UPDATE_TMPL_H_
#define PARAMETER_UPDATE_TMPL_H_

#include "src/parameter/dense_vector_tmpl.h"

namespace brook {

//-----------------------------------------------------------------
// Updater implemented by `real` Updater.
//-----------------------------------------------------------------
template <class ValueType>
class Updater {

typedef DenseVectorTmpl<ValueType> DenseVector;

public:
    Updater() {}
    ~Updater() {}

    virtual void Update(DenseVector& para, const DenseVector& update) = 0;
};

//-----------------------------------------------------------------
// Gradient decent updater
//-----------------------------------------------------------------
template <class ValueType>
class GDUpdater : public Updater<ValueType> {

typedef DenseVectorTmpl<ValueType> DenseVector;

public:
    virtual void Update(DenseVector& para, const DenseVector& gradients) {
        para.Add(gradients);
    }
};

//-----------------------------------------------------------------
// Gradient acent updater
//-----------------------------------------------------------------
template <class ValueType>
class GAUpdater : public Updater<ValueType> {

typedef DenseVectorTmpl<ValueType> DenseVector;

public:
    virtual void Update(DenseVector& para, const DenseVector& gradients) {
        para.Minus(gradients);
    }
};

} // namespace brook

#endif // PARAMETER_UPDATE_TMPL_H_
