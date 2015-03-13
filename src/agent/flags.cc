// Copyright : 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
// Define flags used by agent workers to accept instructions
// from brook scheduler.
//
#include "src/agent/flags.h"

#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "boost/filesystem.hpp"

#include "src/base/common.h"
#include "src/base/scoped_ptr.h"
#include "gflags/gflags.h"
#include "src/sorted_buffer/sorted_buffer.h"
#include "src/strutil/stringprintf.h"
#include "src/strutil/split_string.h"

namespace brook {

const int kDefualtAgentOutputSize = 32 * 1024 * 1024; // 32 MB

} // namespace brook

DEFINE_string(server_workers, "",
              "A set of server workers, each identified by 'hostname:port'."
              "This flag is set only for agent workers, as each agent worker need "
              "to set up networker connections to all server workers.");

DEFINE_int32(num_agent_workers, -1,
             "The num of agent workers.");

DEFINE_int32(agent_worker_id, -1,
             "A zero-based integer index denoting the agent worker id."
             "This flag is set only for agent workers to let them know who they are.");

DEFINE_bool(batch_reduction, false,
            "By default, Brook workers in online reduction mode. Or it can work in batch reduction mode, "
            "the one compatable with Google MapReduce and Hadoop. ");

DEFINE_string(in_memory_file_read, "",
              "in_memory_file_read is a file name, from which the agent can read data.");

DEFINE_string(in_memory_file_write, "",
              "in_memory_file_write is a file name, to which the agent can write data.");

DEFINE_string(fifo_signal_file_read, "",
              "fifo_signal_file_read is a file name, from which the agent can read signal from.");

DEFINE_string(fifo_signal_file_write, "",
              "fifo_signal_file_write is a file name, to which the agent can write signal to.");

DEFINE_string(partition_mode, "",
              "Brook surpport various partition mode such as hash_mod and base_index.");

DEFINE_string(log_filebase, "",
              "The real log filename is log_filebase appended by worker "
              "type, worker id, date, time, process_id, log type and etc.");

DEFINE_int32(max_agent_output_size,
             brook::kDefualtAgentOutputSize,
             "The max size of a map output, in bytes.");

namespace brook {

//-----------------------------------------------------------------------
// Poor guy's singletons:
//-----------------------------------------------------------------------
typedef std::vector<std::string> StringVector;

static scoped_ptr<StringVector>& GetServerWorkers() {
    static scoped_ptr<StringVector> server_workers(new StringVector);
    return server_workers;
}

//-----------------------------------------------------------------------
// Check the correctness of flags.
//-----------------------------------------------------------------------
bool ValidateCommandLineFlags() {
    bool flags_valid = true;

    // Check positive number of server workers. Validates NumServerWorkers().
    SplitStringUsing(FLAGS_server_workers, ",", GetServerWorkers().get());
    if (GetServerWorkers()->size() == 0) {
        LOG(ERROR) << "server_workers must specify one or more server workers.";
        flags_valid = false;
    }

    // Check positive number of agent workers. Validate NumAgentWorkers().
    if (FLAGS_num_agent_workers <= 0) {
        LOG(ERROR) << "agent num must be a positive num";
        flags_valid = false;
    }

    // Check FLAGS_agent_worker_id in range [0, FLAGS_num_agent_workers - 1]
    if (FLAGS_agent_worker_id < 0 || 
        FLAGS_agent_worker_id >= FLAGS_num_agent_workers) {
        LOG(ERROR) << "FLAGS_agent_worker_id must be in range [ 0" 
                   << FLAGS_num_agent_workers-1 << " ]";
        flags_valid = false;
    }

    // Check in_memory_file_read is specified.
    if (FLAGS_in_memory_file_read.empty()) {
        LOG(ERROR) << "FLAGS_in_memory_file_read must be specified.";
        flags_valid = false;
    }

    // Check in_memory_file_write is specified.
    if (FLAGS_in_memory_file_write.empty()) {
        LOG(ERROR) << "FLAGS_in_memory_file_write must be specified.";
        flags_valid = false;
    }

    // Check fifo_signal_file_read is specified.
    if (FLAGS_fifo_signal_file_read.empty()) {
        LOG(ERROR) << "FLAGS_fifo_signal_file_read must be specified.";
        flags_valid = false;
    }

    // Check fifo_signal_file_write is specified.
    if (FLAGS_fifo_signal_file_write.empty()) {
        LOG(ERROR) << "FLAGS_fifo_signal_file_write must be specified.";
        flags_valid = false;
    }

    // Check partition_mode is specified.
    if (FLAGS_partition_mode.empty()) {
        LOG(ERROR) << "FLAGS_partition_mode must be specified.";
        flags_valid = false;
    }

    // Check log_filebase is specified.
    if (FLAGS_log_filebase.empty()) {
        LOG(ERROR) << "FLAGS_log_filebase must be specified.";
        flags_valid = false;
    }
    
    return flags_valid;
}

//----------------------------------------------------------------
// Flag accessors.
//----------------------------------------------------------------

int AgentWorkerId() {
    return FLAGS_agent_worker_id;
}

const StringVector& ServerWorkers() {
    return *GetServerWorkers();
}

int NumServerWorkers() {
    return ServerWorkers().size();
}

int NumAgentWorkers() {
    return FLAGS_num_agent_workers;
}

bool BatchReduction() {
    return FLAGS_batch_reduction;
}

std::string WorkerType() {
    return "Agent";
}

int NumWorkers() {
    return NumAgentWorkers();
}

int WorkerId() {
    return AgentWorkerId();
}

std::string Read_InMemoryFilename() {
    return FLAGS_in_memory_file_read;
}

std::string Write_InMemoryFilename() {
    return FLAGS_in_memory_file_write;
}

std::string Read_FIFO_Filename() {
    return FLAGS_fifo_signal_file_read;
}

std::string Write_FIFO_Filename() {
    return FLAGS_fifo_signal_file_write;
}

std::string PartitionMode() {
    return FLAGS_partition_mode;
}

std::string GetHostName() {
    struct utsname buf;
    if (0 != uname(&buf)) {
        *buf.nodename = '\0';
    }
    return std::string(buf.nodename);
}

std::string GetUserName() {
    const char* username = getenv("USER");
    return username != NULL ? username : getenv("USERNAME");
}

std::string PrintCurrentTime() {
    time_t current_time = time(NULL);
    struct tm broken_down_time;
    CHECK(localtime_r(&current_time, &broken_down_time) == &broken_down_time);
    return StringPrintf("%04d%02d%02d-%02d%02s%02d",
                        1900 + broken_down_time.tm_year,
                        1 + broken_down_time.tm_mon,
                        broken_down_time.tm_mday, broken_down_time.tm_hour,
                        broken_down_time.tm_min, broken_down_time.tm_sec);
}

std::string LogFilebase() {
    // log_filebase := FLAGS_log_filebase + 
    //                 worker_type + worker_index + total_worker_num
    //                 node_name + username + 
    //                 date_time + process_id
    std::string filename_prefix;
    SStringPrintf(&filename_prefix,
                  "%s-%s-%05d-of-%05d.%s.%s.%s.%u",
                  FLAGS_log_filebase.c_str(),
                  WorkerType().c_str(), WorkerId(), NumWorkers(),
                  GetHostName().c_str(),
                  GetUserName().c_str(),
                  PrintCurrentTime().c_str(),
                  getpid());

    return filename_prefix;
}

int AgentOutputBufferSize() {
    return kDefualtAgentOutputSize;
}

} // namespace
