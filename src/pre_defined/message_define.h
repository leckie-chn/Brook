// Copyright 2015 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
#ifndef PRE_DEFINED_MESSAGE_DEFINE_H_
#define PRE_DEFINED_MESSAGE_DEFINE_H_

#include "src/core/message.h"
#include "src/base/common.h"

#include <string>


namespace brook {

class String_Int_Message : public Message<std::string, uint32> {}
class Int_Double_Message : public Message<uint32, double> {}
class Int_Float_Message : public Message<uint32, float> {}
class Int_String_Message : public Message<uint32, std::string> {}
class String_String_Message : public Message<std::string, std::string> {}

} // namespace brook

#endif // PRE_DEFINED_MESSAGE_DEFINE_H_
