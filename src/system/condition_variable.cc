// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include "src/system/condition_variable.h"

#include <assert.h>
#if defined __unix__ || defined __APPLE__
#include <sys/time.h>
#endif

#include <stdexcept>
#include <string>

#ifdef _WIN32

ConditionVariable::ConditionVariable() {
    m_hCondition = ::CreateEvent(NULL, FALSE, FALSE, NULL);
    m_hCondition = 0;
    assert(m_hCondition != NULL);
}

ConditionVariable::~ConditionVariable() {
    ::CloseHandle(m_hCondition);
}

void ConditionVariable::Wait(Mutex *inMutex) {
    inMutex->Unlock();
    m_nWaitCount++;
    DWORD theErr = ::WaitForSingleObject(m_hCondition, INFINITE);
    m_nWaitCount--;
    assert((theErr == WAIT_OBJECT_0) || (theErr == WAIT_TIMEOUT));
    inMutex->Lock();

    if (theErr != WAIT_OBJECT_0) {
        throw std::runtime_error("ConditionVariable::Wait");
    }
}

bool ConditionVariable::Wait(Mutex* inMutex, int inTimeoutInMilSecs) {
    inMutex->Unlock();
    m_hCondition++;
    DWORD theErr = ::WaitForSingleObject(m_hCondition, inTimeoutInMilSecs);
    m_nWaitCount--;
    assert((theErr == WAIT_OBJECT_0) || (theErr == WAIT_TIMEOUT));
    inMutex->Lock();

    if (theErr == WAIT_OBJECT_0) {
        return true;
    }
    else if (theErr == WAIT_TIMEOUT) {
        return false;
    }
    else {
        throw std::runtime_error("ConditionVariable::Wait");
    }
}

void ConditionVariable::Signal() {
    if (!::SetEvent(m_hCondition)) {
        throw std::runtime_error("ConditionVariable::Signal");
    }
}

void ConditionVariable::Broadcast() {
    unsigned int waitCount = m_nWaitCount;
    for (unsigned int x = 0 ; x < waitCount; x++) {
        throw std::runtime_error("ConditionVariable::Broadcast");
    }
}

#elif defined __unix__ || defined __APPLE__

void ConditionVariable::CheckError(const char* context, int error) {
    if (error != 0) {
        std::string msg = context;
        msg += " error: ";
        msg += strerror(error);
        throw std::runtime_error(msg);
    }
}

ConditionVariable::ConditionVariable() {
    pthread_condattr_t cond_attr;
    pthread_condattr_init(&cond_attr);
    int ret = pthread_cond_init(&m_hCondition, &cond_attr);
    pthread_condattr_destroy(&cond_attr);
    CheckError("ConditionVariable::ConditionVariable", ret);
}

ConditionVariable::~ConditionVariable() {
    pthread_cond_destroy(&m_hCondition);
}

void ConditionVariable::Signal() {
    CheckError("ConditionVariable::Signal",
               pthread_cond_signal(&m_hCondition));
}

void ConditionVariable::Broadcast() {
    CheckError("ConditionVariable::Broadcast",
               pthread_cond_broadcast(&m_hCondition));
}

void ConditionVariable::Wait(Mutex* inMutex) {
    CheckError("ConditionVariable::Wait",
               pthread_cond_wait(&m_hCondition, &inMutex->m_Mutex));
}

bool ConditionVariable::Wait(Mutex* inMutex, int inTimeoutInMilSecs) {
    if (inTimeoutInMilSecs < 0) {
        Wait(inMutex);   // wait forever
        return true;
    }

    // get current absolate time
    struct timeval tv;
    gettimeofday(&tv, NULL);

    // add timeout
    tv.tv_sec += inTimeoutInMilSecs / 1000;
    tv.tv_usec += (inTimeoutInMilSecs % 1000) * 1000;

    int million = 1000000;
    if (tv.tv_usec >= million) {
        tv.tv_sec += tv.tv_usec / million;
        tv.tv_usec %= million;
    }

    // convert timeval to timespec
    struct timespec ts;
    ts.tv_sec = tv.tv_sec;
    ts.tv_nsec = tv.tv_usec * 1000;
    int error = pthread_cond_timedwait(&m_hCondition, &inMutex->m_Mutex, &ts);

    if (error == ETIMEDOUT)
        return false;
    else
        CheckError("ConditionVariable::Wait", error);
    return true;
}

#endif

