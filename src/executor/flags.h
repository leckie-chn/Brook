// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef EXECUTOR_FLAGS_H_
#define EXECUTOR_FLAGS_H_

#include <string>
#include <vector>

#include "gflags/gflags.h"
#include "src/util/common.h"


namespace brook {

int TotalWorkerNum();
bool ValidateCommandLineFlags();   
int WorkerID();
int NumAgent();
int NumServer();
int64 MaxFeatures();
std::string WorkerType();
const std::string Cache_file_update();
const std::string Cache_file_parameter();
const std::string Signal_file_update();
const std::string Signal_file_parameter();
std::string GetHostName();
std::string GetUserName();
std::string PrintCurrentTime();
const std::string LogFilebase();
int Shard(uint64 index);


} // namespace brook


#endif // EXECUTOR_FLAGS_H_
