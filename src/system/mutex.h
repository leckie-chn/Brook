// Copyright 2015 PKU-Cloud .
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef SYSTEM_MUTEX_H_
#define SYSTEM_MUTEX_H_

# if defined _WIN32
# ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
# endif

# if defined _WIN32_WINNT
#  define _WIN32_WINNT 0x0501 // windows xp
# endif

# define NOMINMAX 1
#include <windows.h>
#elif defined __unix__ || defined __APPLE__
#include <pthread.h>
#else
# error Unknown platform
#endif

#include <assert.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <stdexcept>

#include "src/system/scoped_locker.h"

#if defined _WIN32

// if _WIN32_WINNT not defined, TryEnterCriticalSection will not be declared
// in windows.h
extern "C" WINBASEAPI
BOOL WINAPI TryEnterCriticalSection(
    __inout LPCRITICAL_SECTION lpCritialSection);

class Mutex {
public:
    typedef ScopedLocker<Mutex> Locker;
public:
    explicit Mutex(bool recursive = true) {
        ::InitializeCriticalSection(&m_Mutex);
    }

    ~Mutex() {
        ::DeleteCriticalSection(&m_Mutex);
    }

    void Lock() {
        ::EnterCriticalSection(&m_Mutex);
    }

    bool TryLock() {
        return ::TryEnterCriticalSection(&m_Mutex) != FALSE;
    }

    void Unlock() {
        ::LeaveCriticalSection(&m_Mutex);
    }

private:
    // In Microsoft Windows server 2003 service pack 1 and later version of
    // Windows, the lockCount field is parsed as follows:
    // * The lowest bit shows the lock status. If this bit is 0, the critical
    //   section is locked; If it is 1, the critical section is not locked.
    // * The next bit shows whether a thread has been woken for this lock.
    //   If this bit is 0, then a thread has been woken for this lock; If it
    //   is 1, no thread has been woken.
    // * The remaining bits are the ones-complement of the number of threads
    //   waiting for the lock.
    static bool IsNewBehavior() {
        static bool result = DoIsNewBehavior();
        return result;
    }
    static bool DoIsNewBehavior() {
        Mutex mutex;
        int old_lock_count = mutex.m_Mutex.LockCount;
        mutex.Lock();
        int new_lock_count = mutex.m_Mutex.LockCount;
        return new_lock_count < old_lock_count;
    }
private:
    Mutex(const Mutex& right);
    Mutex& operator = (const Mutex& right);
    CRITICAL_SECTION m_Mutex;
    friend class Cond;
};

#elif defined __unix__ || defined __APPLE__


#endif // SYSTEM_MUTEX_H_
