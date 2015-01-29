// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#ifndef MRML_FLAGS_H_
#define MRML_FLAGS_H_

#include <string>
#include <vector>

#include "src/base/common.h"
#include "src/mrml/mapreduce.h"

#include "gflags/gflags.h"


namespace brook {

typedef std::vector<std::string> StringVector;
typedef std::vector<uint16> IntVector;

bool IAmAgentWorker();
bool IAmServerWorker();
const char* WorkerType();
int WorkerId();
int NumAgentWorkers();
int NumServerWorkers();
int NumWorkers();
const std::string& GetMapperClass();
const std::string& GetReducerClass();
const std::string& OutputFormat();
const std::string& InputFormat();
const IntVector& ServerWorkers();
const IntVector& AgentWorkers();
const StringVector& OutputFiles();
const std::string& CacheFileValuePattern();
const std::string& CacheFileModelPattern();
std::string GetHostName();
std::string GetUserName();
std::string PrintCurrentTime();
std::string LogFilebase();
std::string ReduceInputBufferFilebase();
int ReduceInputBufferSize();
int MapOutputBufferSize();
void ChangeStringListToIntList(StringVector& str_list,
                               IntVector* int_list);
bool ValidateCommandLineFlags();
bool BatchReduction();
Mapper* CreateMapper();
ReducerBase* CreateReducer();

} // brook

#endif // MRML_FLAGS_H_
