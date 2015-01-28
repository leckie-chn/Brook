// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/base/common.h"
#include "src/mrml/flags.h"
#include "src/mrml/mapreduce.h"

extern bool brook::Initialize(int argc, char** argv);
extern bool brook::IAmAgentWorker();
extern void brook::MapWork();
extern void brook::ReduceWork();
extern void Finalize();

//---------------------------------------------------------------------
// pre-defined main function 
//---------------------------------------------------------------------

int main(int argc, char** argv) {
    // Parse command line flags, leaving argc unchanged, but reaarange
    // the arguments in argv sp that the flags are all at the beginning.
    google::ParseCommandLineFlags(&argc, &argv, false);

    if (!brook::Initialize(int argc, char** argv)) {
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
