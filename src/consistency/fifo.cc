// Copyright 2015 PKU-Cloud.
// Auhtor : Chao Ma (mctt90@gmail.com)
//
#include "src/consistency/fifo.h"

#define EVERYONE_CAN_READ_AND_WRITE 0666

namespace brook {

const int MAXS = 10;

void MkFifo(std::string filename) {
    unlink(filename.c_str()); // Ensure close the pre-created file.
    if (mkfifo(filename.c_str(), EVERYONE_CAN_READ_AND_WRITE) != 0) {
        LOG(FATAL) << "Create fifo file failed.";
    }
}

void DeleteFifo(std::string filename) {
    unlink(filename.c_str());
}

int OpenReadFifo(std::string filename) {
    int fp = open(filename.c_str(), O_RDONLY);
    return fp;
}

int OpenWriteFifo(std::string filename) {
    int fp = open(filename.c_str(), O_WRONLY);
    return fp;
}

int FifoReadNum(int fp) {
    char buf[MAXS]; 
    size_t len = read(fp, buf, MAXS);
    buf[len] = '\0';
    int num = 0;
    int i = 0;
    for (char *p = buf; i < len;  ++i) {
        num = num * 10 + *p - '0';
        p++;
    }
    return num;
}

void WriteNum(int num, int fp) {
    std::stringstream ss;
    ss << num;
    std::string str_num(ss.str());
    write(fp, str_num.data(), str_num.size());
}

} // namespace brook
