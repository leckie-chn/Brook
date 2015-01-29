// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
// Pre-defined mappers and reducers
//
#ifndef MRML_MAPPERS_AND_REDUCERS_H_
#define MRML_MAPPERS_AND_REDUCERS_H_

#include <map>
#include <string>

#include "src/mrml/mapreduce.h"
#include "src/strutil/split_string.h"

using namespace std;
using std::map;
using std::string;


namespace brook {

//-----------------------------------------------------------------------------
// Predefined mappers and reducers
//-----------------------------------------------------------------------------
class IndentityMapper : public Mapper {
    virtual void Map(const string& key, const string& value) {
        Output(key, value);
    }
};
// REGISTER_MAPPER(IndentityMapper);

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

template<typename ValueType>
class BatchSumReducer : public BatchReducer {
public:
    void Start() {}

    void Reduce(const string& key, ReduceInputIterator* values) {
        ValueType sum = 0;
        for (; !values->Done(); values->Next()) {
            istringstream parser(values->value());
            ValueType count;
            parser >> count;
            sum += count;
        }
        ostringstream formater;
        formater << sum;
        Output(key, formater.str());
    }
};

class BatchIntegerSumReducer : public BatchSumReducer<int> {};
class BatchFloatSumReducer : public BatchSumReducer<float> {};
class BatchDoubleSumReducer : public BatchSumReducer<double>{};

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
// REGISTER_INCREMENTAL_REDUCER(SumFloatReducer);
// REGISTER_INCREMENTAL_REDUCER(SumDoubleReducer);

} // namespace brook

#endif // MRML_MAPPERS_AND_REDUCERS_H_
