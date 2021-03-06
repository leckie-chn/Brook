// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef PARAMETER_RANDOM_QUEUE_TMPL_H_
#define PARAMETER_RANDOM_QUEUE_TMPL_H_

#include "src/util/common.h"

#include <vector>

namespace brook {

//------------------------------------------------------------
// A naive implementation of RandomQueue using STL Vector.
//------------------------------------------------------------
template <class ValueType>
class RandomQueueTmpl {
public:   
    RandomQueueTmpl() {}
    ~RandomQueueTmpl() {}

    void Push(ValueType value) {
        queue_.push_back(value);
    }

    ValueType Pop() {
        ValueType res = queue_[0];
        queue_.erase(queue_.begin());
        return res;
    }

    ValueType Get(int index) {
        CHECK_GE(index, 0);
        CHECK_LT(index, queue_.size());
        return queue_[index];
    }

    void Set(int index, ValueType value) {
        CHECK_GE(index, 0);
        CHECK_LT(index, queue_.size());
        queue_[index] = value;
    }

    size_t Size() {
        return queue_.size();
    }

private:
    std::vector<ValueType> queue_;
};

} // namespace brook

#endif // PARAMETER_RANDOM_QUEUE_TMPL_H_
