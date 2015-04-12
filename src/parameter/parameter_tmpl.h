// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
// Parameter is an important class which been used in server.
//
#ifndef PARAMETER_PARAMETER_TMPL_H_
#define PARAMETER_PARAMETER_TMPL_H_

#include "src/parameter/dense_vector_tmpl.h"
#include "src/parameter/version_buffer_tmpl.h"
#include "src/parameter/update_tmpl.h"

#include "src/util/bitmap.h"
#include "src/util/scoped_ptr.h"

#include <vector>

namespace brook {

template <class ValueType>
class Parameter {

typedef DenseVectorTmpl<ValueType> DenseVector;
typedef VersionBufferTmpl<ValueType> VersionBuffer;
typedef UpdaterTmpl<ValueType> Updater;

public:
    Parameter(int bounded_staleness, uint64 feature_num, int32 num_agent) {
        CHECK_GE(bounded_staleness, 0);
        CHECK_GT(feature_num, 0);
        CHECK_GT(num_agent, 0);

        bounded_staleness_ = bounded_staleness;
        row_size_ = bounded_staleness_ + 1;
        feature_num_ = feature_num;
        num_agent_ = num_agent;

        version_buffer_.reset(new VersionBuffer(bounded_staleness_, 
                              feature_num_, num_agent_));
    }

    ~Parameter() {}
    
    void Do_update() {
        // doing update
        update_->Update((*parameter_), *version_buffer_.GetOldestUpdates());
    }

private:
    scoped_ptr<VersionBuffer> version_buffer_;        // the buffer to store the version update.
    scoped_ptr<DenseVector> parameter_;               // parameter vector.

    scoped_ptr<Updater> update_;

    int bounded_staleness_;                 // bounded_staleness_ decides the row size of version buffer.
    int row_size_;                          // row_size_ = bounded_staleness_ + 1.
    uint64 feature_num_;                    // the size of parameter, this may be vary large.
    int num_agent_;
};
 
} // namespace brook

#endif // PARAMETER_PARAMETER_TMPL_H_
