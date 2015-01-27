// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#ifndef MRML_FLAGS_H_
#define MRML_FLAGS_H_

namespace brook {

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
const StringVector& ServerWorkers();
const StringVector& AgentWorkers();
const StringVector& OutputFiles();
const std::string& GetCacheFileValue();
const std::string& GetCacheFileModel();
std::string& GetHostName();
std::string& GetUserName();
std::string PrintCurrentTime();
std::string LogFilebase();
void ChangeStringListToIntList(const StringVector& str_list,
                               const vector<int>* int_list);
bool ValidateCommandLineFlags();

} // brook

#endif // MRML_FLAGS_H_
