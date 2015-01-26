#include "src/base/logging.h"

int main() {

    InitializeLogger("/tmp/info.log", "/tmp/warn.log", "/tmp/erro.log");
    LOG(INFO)     << "An info message going into /tmp/info.log";
    LOG(WARNING)  << "An warn message going into /tmp/warn.log";
    LOG(ERROR)    << "An erro message going into /tmp/erro.log";
    LOG(FATAL)    << "An fatal message going into /tmp/erro.log, "
                  << "and kills current process by a segmentation fault.";

    return 0;
}
