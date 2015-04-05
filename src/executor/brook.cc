// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/executor/brook.h"

#include <mpi.h>

namespace brook {

bool Initialize(int argc, char** argv) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    return true;
}

void Finalize() {
    // After all, finalize MPI.
    MPI_Finalize();
}


} // namespace brook
