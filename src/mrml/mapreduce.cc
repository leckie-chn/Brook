// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/mrml/mapreduce.h"

#include "src/base/common.h"
#include "src/base/logging.h"
#include "src/mrml/flags.h"
#include "src/mrml/mappers_and_reducers.h"
#include "src/strutil/split_string.h"


CLASS_REGISTER_IMPLEMENT_REGISTRY(mapreduce_lite_mapper_registry,
                                  brook::Mapper);

CLASS_REGISTER_IMPLEMENT_REGISTRY(mapreduce_lite_incremental_reducer_registry,
                                  brook::IncrementalReducer);

CLASS_REGISTER_IMPLEMENT_REGISTRY(mapreduce_lite_batch_reducer_registry,
                                  brook::BatchReducer);

namespace brook {

using namespace std;
using std::map;
using std::string;
using std::vector;


//-----------------------------------------------------------------------------------
// Implementation of ReducerBase:
//-----------------------------------------------------------------------------------
void ReducerBase::Output(const string& key, const string& value) {

}

void ReducerBase::OutputToChannel(int channel,
                                  const string& key, const string& value)
{
    
}

const string& ReducerBase::GetOutputFormat() const {
    
}

int ReducerBase::NumOutputChannels() const {
    return 0;
}

//-----------------------------------------------------------------------------------
// Implementation of Mapper
//-----------------------------------------------------------------------------------
int Mapper::Shard(const string& key, int num_reduce_workers) {

}

void Mapper::Output(const string& key, const string& value) {
    
}

void Mapper::OutputToShard(int reduce_shard,
                           const string& key, const string& value)
{

}

void Mapper::OutputToAllShards(const string& key, const string& value) {
    
}

const string& Mapper::CurrentInputFilename() const {

}

const string& Mapper::GetInputFormat() const {
    
}

const string& Mapper::GetOutputFormat() const {

}

int Mapper::GetNumReduceShards() const {
    return 0;
}


} // namespace brook
