// Copyright 2015 PKU-Cloud
// Author Yan Ni(leckie.dove@gmail.com)

#include <src/util/bitmap.h>
#include "gtest/gtest.h"
#include <set>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

TEST(BitMapTest, Init){
	brook::bitmap obj(10);
	vector<size_t> list;
	obj.set(1);
	obj.set(4);
	obj.set(7);

	obj.ListGen(list);

	EXPECT_EQ(list.size(), 3);
	EXPECT_EQ(obj.test(1), true);
	EXPECT_EQ(obj.test(0), false);
}

TEST(BitMapTest, Compress){
	brook::bitmap obj(100);
	vector<size_t> vec;
	obj.set(2);
	obj.set(10);
	obj.set(15);
	obj.set(75);

	obj.compress();

	obj.decompress();
	EXPECT_EQ(obj.test(2), true);
	EXPECT_EQ(obj.test(10), true);
	EXPECT_EQ(obj.test(15), true);
	EXPECT_EQ(obj.test(75), true);

	obj.ListGen(vec);
	EXPECT_EQ(vec.size(), 4);
}

TEST(BitMapTest, RandomTest){
	brook::bitmap obj(10000);
	std::set<int> flag;
	vector<size_t> vec;
	for (int i = 0; i < 5000; i++){
		int t = rand() % 10000;
		flag.insert(t);
		obj.set(t);
	}

	obj.compress();

	obj.decompress();
	for (set<int>::iterator iter = flag.begin(); iter != flag.end(); iter++)
		EXPECT_EQ(obj.test(*iter), true);

	obj.ListGen(vec);
	EXPECT_EQ(vec.size(), flag.size());
}
