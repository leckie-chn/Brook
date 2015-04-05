// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef SYSTEM_CONDITION_VARIABLE_H_
#define SYSTEM_CONDITION_VARIABLE_H_

#ifndef _WIN32
#if defined __unix__ || defined __APPLE__
#include <pthread.h>
#endif
#endif

#include <assert.h>
#include "src/system/mutex.h"

class ConditionVariable {
public:
    ConditionVariable();
    ~ConditionVariable();

    void Signal();
    void Broadcast();

    bool Wait(Mutex* inMutex, int inTimeoutInMilSecs);
    void Wait(Mutex* inMutex);

private:
#if defined _WIN32
    HANDLE m_hCondition;
    unsigned int m_nWaitCount;
#elif defined __unix__ || defined __APPLE__
    pthread_cond_t m_hCondition;
#endif
    static void CheckError(const char* context, int error);
};

#endif // SYSTEM_CONDITION_VARIABLE_H_
