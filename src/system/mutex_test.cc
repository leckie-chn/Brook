// Copyright 2015 PKU-Cloud.
// Auhtor : Chao Ma (mctt90@gmail.com)
//
#include "gtest/gtest.h"
#include "src/system/mutex.h"

TEST(Mutex, Lock) {
    Mutex mutex;
    mutex.Lock();
    mutex.Unlock();
}

TEST(Mutex, Locker) {
    Mutex mutex;
    {
        MutexLocker locker(&mutex);
    }
}

TEST(Mutex, LockerWithException) {
    Mutex mutex;
    try {
        MutexLocker locker(&mutex);
        throw 0;
    } catch(...) {
        // ignore
    }
}
