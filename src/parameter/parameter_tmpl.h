// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
// Parameter is an important class which been used both in server and 
// agent workers.
//
#ifndef PARAMETER_PARAMETER_TMPL_H_
#define PARAMETER_PARAMETER_TMPL_H_

namespace brook {

class Parameter {

};

template<class ValueType>
class DenseParameter : public Parameter {

};


template<class KeyType, class ValueType>
class SparseParameter: public Parameter {

};

} // namespace brook

#endif // PARAMETER_PARAMETER_TMPL_H_
