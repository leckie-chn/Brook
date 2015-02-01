// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#include "src/collection/collection.h"

#include "src/base/common.h"
#include "src/base/scoped_ptr.h"
#include "src/base/logging.h"
#include "src/mrml/flags.h"
#include "src/mrml/typedef.h"
#include "src/mrml/protofile.pb.h"
#include "src/in_memory_store/sparse_vector.h"
#include "src/in_memory_store/dense_vector.h"
#include "src/in_memory_store/vector_iterator.h"

#include <mpi.h>
#include <string>

namespace brook {

typedef MapperOutput ModelBroadcast;

//---------------------------------------------------------------------------------------------
// Implementation of kv_store broadcast:
//---------------------------------------------------------------------------------------------
void KVStoreBroadcast(RealVector* rv) {

    LOG(INFO) << "Start broadcast model ...";
    // Initialize a new KV_Iterator
    scoped_ptr<RealVectorIterator> vec_iter;
    vec_iter.reset(new RealVectorIterator);
    vec_iter->Initialize(rv);
    LOG(INFO) << "Creating kv_store_iter succeeded ...";

    std::string key, value;
    LOG(INFO) << "Start reading key value pair from kv_store.";
    // Reading key, value in the specified kv_store.
    while (true) {
        if (!vec_iter->HasNext(key, value)) {
            break;
        }
        ModelBroadcast mb;
        mb.set_key(key);
        mb.set_value(value);
    }
    CollectionNotifyFinished();
}

} // namespace brook
