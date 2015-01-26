// Copyright 2014 PKU-Cloud.
// Author: Chao Ma (mctt90@gmail.com)
//
// Wrappers for several pseudo－random number generators used in LDA, including
// the default unix RNG(random number generators), and RNGs provided in Boost
// library. We suggest not using unix RNG due to randomness in application.
//
#ifndef BASE_RANDOM_H_
#define BASE_RANDOM_H_

#include "src/base/common.h"
#include "boost/random.hpp"

// The RNG wrapper interface
class Random {
public:
    Random() {}

    virtual ~Random() {}

    // Seed the RNG using specified seed or current time (if seed < 0).
    // In order to achieve maximun randomness we use current time in
    // millsecond as the seed. Note that it is not a good idea to 
    // seed with current time in second when multiple random number
    // sequences are required, which usually produces correlated number
    // sequences and results in poor randomness.
    virtual void SeedRNG(int seed) = 0;

    // Generate a random float value in the range of [0,1] from the
    // uniform distribution.
    virtual double RandDouble() = 0;

    // Generate a random integer value in the range of [0, bound] from the
    // uniform distribution.
    virtual int RandInt(int bound) {
        return static_cast<int>(RandDouble * bound);
    }

    // Get tick count of the day, used as random seed
    static uint32 GetTickCount();
};

#endif //BASE_RANDOM_H_
