// Copyright 2015 PKU-Cloud.
// Author : Chao Ma (mctt90@gmail.com)
//
#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "src/in_memory_store/sparse_vector.h"
#include "src/in_memory_store/dense_vector.h"
#include "src/in_memory_store/vector_iterator.h"

using std::string;
using brook::SparseVector;
using brook::DenseVector;
using brook::SparseVectorIterator;
using brook::DenseVectorIterator;

typedef SparseVector<string, float> RealSparseVector;
typedef DenseVector<float> RealDenseVector;
typedef SparseVectorIterator<string, float> RealSparseVectorIter;
typedef DenseVectorIterator<float> RealDenseVectorIter;

TEST(SparseVectorIterator, SparseIterator) {
    RealSparseVector rsv;
    rsv.set("1", 0.112);
    rsv.set("2", 1.455);
    rsv.set("3", 2.345);
    RealSparseVectorIter iter;
    iter.Initialize(&rsv);
    string key, value;
    
    while (true) {
        if (!iter.HasNext(key, value)) {
            break;
        }
        std::cout << key << " : " << value << std::endl;
    }
}

TEST(DenseVectorIterator, DenseIterator) {
    RealDenseVector rdv;
    rdv.push_back(4.321);
    rdv.push_back(43.21);
    rdv.push_back(0.432);
    RealDenseVectorIter iter;
    iter.Initialize(&rdv);
    string key, value;

    while (true) {
        if (!iter.HasNext(key, value)) {
            break;
        }
        std::cout << key << " : " << value << std::endl;
    }
}
