// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/mrml/mapreduce.h"

#include "src/base/common.h"
#include "src/base/logging.h"
#include "src/mrml/flags.h"
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

//-----------------------------------------------------------------------------
// Predefined mappers and reducers
//-----------------------------------------------------------------------------
class IndentityMapper : public Mapper {
    virtual void Map(const string& key, const string& value) {
        Output(key, value);
    }
};
REGISTER_MAPPER(IndentityMapper);

class WordCountMapper : public Mapper {
public:
    void Map(const std::string& key, const std::string& value) {
        std::vector<std::string> words;
        SplitStringUsing(value, " ", &words);
        for (int i = 0 ; i < words.size() ; i++) {
            ++combiner_result[words[i]];
        }
    }

    void Flush() {
        for (map<string, int>::const_iterator i = combiner_result.begin();
             i != combiner_result.end(); i++)
        {
            ostringstream formater;
            formater << i -> second;
            Output(i->first, formater.str());
        }
        combiner_result.clear();
    }
private:
    map<string, int> combiner_result;
};
REGISTER_MAPPER(WordCountMapper);

template <typename ValueType>
class SumReducer : public IncrementalReducer {
public:
    virtual void* BeginReduce(const string& key, const string& value) {
        std::istringstream is(value);
        ValueType* count = new ValueType;
        is >> *count;
        return count;
    }
    virtual void PartialReduce(const string& key, const string& value,
                               void* partial_sum)
    {
        std::istringstream is(value);
        ValueType count = 0;
        is >> count;
        *static_cast<ValueType*>(partial_sum) += count;
    }
    virtual void EndReduce(const string& key, void* final_sum) {
        ValueType* p = static_cast<ValueType*>(final_sum);
        std::ostringstream os;
        os << *p;
        Output(key, os.str());
        delete p;
    }
};

class SumIntegerReducer : public SumReducer<int> {};
class SumFloatReducer : public SumReducer<float> {};
class SumDoubleReducer : public SumReducer<double> {};

REGISTER_INCREMENTAL_REDUCER(SumIntegerReducer);
REGISTER_INCREMENTAL_REDUCER(SumFloatReducer);
REGISTER_INCREMENTAL_REDUCER(SumDoubleReducer);

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
