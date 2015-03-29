// Copyright 2015 PKU-Cloud.
// Auhtor : Chao Ma (mctt90@gmail.com)
//
// Fifo is a wrapper for linux fifo mechanism.
//
#ifndef CONSISTENCY_FIFO_H_
#define CONSISTENCY_FIFO_H_

#include "src/util/common.h"
#include "src/util/logging.h"

#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define EVERYONE_CAN_READ_AND_WRITE 0666

namespace brook {

class Fifo {
public:
    Fifo(std::string filename) : file_name_(filename) {
        unlink(file_name_.c_str()); // Ensure close the pre-created file.
        if(mkfifo(file_name_.c_str(), EVERYONE_CAN_READ_AND_WRITE) != 0) {
            LOG(FATAL) << "Create fifo file failed.";
        }
    }

    ~Fifo() {
        unlink(file_name_.c_str());
    }

private:
    std::string file_name_;


};

} // namespace brook


#endif // CONSISTENCY_FIFO_H_
