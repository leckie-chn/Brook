// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
// Message is the interface that store the key value pair.
// the type of key and value is undefined, so we use template,
// the type-specified messages are defined in src/pre_defined.
//
#ifndef CORE_MESSAGE_H_
#define CORE_MESSAGE_H_

#include "src/base/common.h"

#include <string>
#include <sstream>

namespace brook {

template <typename K, typename V>
class Message {
public:
    Message() {};
    ~Message() {};

    // This method used by TextRead, which read 
    // text record to set message.
    void SetKeyValueUsingString(std::string& key, 
                                std::string& value) {
        istringstream parser_key(key);
        parser_key >> this->key_;
        istringstream parser_value(value);
        parser_value >> this->value_;
    }

    K& GetKey() const {
        return key_;
    }

    V& GetValue() const {
        return value_;
    }

private:
    K key_;
    V value_;

    DISALLOW_COPY_AND_ASSIGN(Message);
};

} // namespace brook

#endif // CORE_MESSAGE_H_
