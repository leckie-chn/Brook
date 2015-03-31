// Copyright 2015 PKU-Cloud.
// Auhtor : Chao Ma (mctt90@gmail.com)
//
// Fifo is a very simple wrapper for linux fifo mechanism.
//
#ifndef CONSISTENCY_FIFO_H_
#define CONSISTENCY_FIFO_H_

#include "src/util/common.h"
#include "src/util/logging.h"

#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

namespace brook {


void MkFifo(std::string);

void DeleteFifo(std::string);

int OpenReadFifo(std::string);

int OpenWriteFifo(std::string);

int FifoReadNum(int);

void WriteNum(int, int);

} // namespace brook


#endif // CONSISTENCY_FIFO_H_
