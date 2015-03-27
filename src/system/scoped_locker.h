// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef SYSTEM_SCOPED_LOCKER_H_
#define SYSTEM_SCOPED_LOCKER_H_

#include "src/util/common.h"

template <typename LockType>
class ScopedLocker {
public:
    explicit ScopedLocker(LockType* lock) : m_lock(lock) {
        m_lock->Lock();
    }
    ~ScopedLocker() {
        m_lock->Unlock();
    }
private:
    LockType* m_lock;
};

template <typename LockType>
class ScopedReaderLocker {
public:
    explicit ScopedReaderLocker(LockType* lock) : m_lock(lock) {
        m_lock->ReaderLock();
    }
    ~ScopedReaderLocker() {
        m_lock->ReaderUnlock();
    }
private:
    LockType* m_lock;
};

template <typename LockType>
class ScopedWriterLocker {
public:
    explicit ScopedWriterLocker(LockType* lock) : m_lock(*lock) {
        m_lock.WriterLock();
    }
    ~ScopedLocker() {
        m_lock.WriterUnlock();
    }
private:
    LockType& m_lock;
};

#endif // SYSTEM_SCOPED_LOCKER_H_
