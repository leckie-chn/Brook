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

//-----------------------------------------------------------------------------
// Check the correctness of flags.
//-----------------------------------------------------------------------------
bool ValidateCommandLineFlags();

//-----------------------------------------------------------------------------
// Invoke ValidateCommandLineFlags() before using the following accessors.
//-----------------------------------------------------------------------------
int AgentWorkerId();
const std::vector<std::string>& ServerWorkers();
int NumServerWorkers();
int NumAgentWorkers();
bool BatchReduction();
std::string WorkerType();
int  NumWorkers();
int WorkerId();
std::string Read_InMemoryFilename();
std::string Write_InMemoryFilename();
std::string Read_FIFO_Filename();
std::string Write_FIFO_Filename();
std::string PartitionMode();
std::string GetHostName();
std::string GetUserName();
std::string PrintCurrentTime();
std::string LogFilebase();
int AgentOutputBufferSize();
int64 FeatureNumber();

} // namespace brook

#endif // AGENT_FLAGS_H_
