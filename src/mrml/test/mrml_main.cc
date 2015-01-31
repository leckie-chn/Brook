// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/base/common.h"
#include "src/mrml/flags.h"
#include "src/mrml/mapreduce.h"
#include "src/in_memory_store/sparse_vector.h"

typedef brook::SparseVector<std::string, uint32> RealVector;

extern bool brook::Initialize(int, char**, RealVector*);
extern bool brook::IAmAgentWorker();
extern void brook::MapWork();
extern void brook::ReduceWork();
extern void brook::Finalize();

//---------------------------------------------------------------------
// pre-defined main function 
//---------------------------------------------------------------------

int main(int argc, char** argv) {
    // Parse command line flags, leaving argc unchanged, but reaarange
    // the arguments in argv sp that the flags are all at the beginning.
    google::ParseCommandLineFlags(&argc, &argv, false);

    // Create a sparse in-memory key-value store
    RealVector* kv_store(new RealVector);

    if (!brook::Initialize(argc, argv, kv_store)) {
        LOG(ERROR) << "Initalization of Brook failed.";
        return -1;
    }

    if (brook::IAmAgentWorker()) {
        brook::MapWork();
    } else {
        brook::ReduceWork();
    }

    brook::Finalize();
    return 0;
}
