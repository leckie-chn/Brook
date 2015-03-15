// Copyright : 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
// Define flags used by agent workers to accept instructions
// from brook scheduler.
//
#ifndef AGENT_FLAGS_H_
#define AGENT_FLAGS_H_

#include <string>
#include <vector>

#include "gflags/gflags.h"

namespace brook {

bool ValidateCommandLineFlags();
int NumAgentWorkers();
int NumServerWorkers();
int NumWorkers();
int WorkerId();
bool IAmAgent();
const char* WorkerType();
bool SortBasedShuffle();
std::string ModelCacheFile();
std::string SubDataCacheFile();
std::string ModelFIFOFile();
std::string SubDataFIFOFile();
std::string OutputFormat();
std::string GetHostName();
std::string GetUserName();
std::string PrintCurrentTime();
std::string LogFilebase();

} // namespace brook

#endif // AGENT_FLAGS_H_
