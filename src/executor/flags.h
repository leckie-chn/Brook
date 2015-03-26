// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef EXECUTOR_FLAGS_H_
#define EXECUTOR_FLAGS_H_

#include <string>
#include <vector>

#include "gflags/gflags.h"


namespace brook {

int TotalWorkerNum();
bool ValidateCommandLineFlags();   
int WorkerID();
std::string WorkerType();

} // namespace brook


#endif // EXECUTOR_FLAGS_H_
