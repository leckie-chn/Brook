// Copyright 2015 PKU-Cloud
// Author Yan Ni(leckie.dove@gmail.com)

#include "gtest/gtest.h"
#include "src/parameter/bitmap.h"

#include <set>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

TEST(BitMapTest, Init){
	brook::bitmap obj(10);
	obj.set(1);
	obj.set(4);
	obj.set(7);

	vector<size_t> *list = obj.ListGen();

	EXPECT_EQ(list->size(), 3);
	EXPECT_EQ(obj.test(1), true);
	EXPECT_EQ(obj.test(0), false);
}

TEST(BitMapTest, Compress){
	brook::bitmap obj(100);

	obj.set(2);
	obj.set(10);
	obj.set(15);
	obj.set(75);

	string * compressed = obj.Compress();

	brook::bitmap obj2(*compressed, 100);
	EXPECT_EQ(obj2.test(2), true);
	EXPECT_EQ(obj2.test(10), true);
	EXPECT_EQ(obj2.test(15), true);
	EXPECT_EQ(obj2.test(75), true);
	EXPECT_EQ(obj.ListGen()->size(), 4);

	delete compressed;
}

TEST(BitMapTest, RandomTest){
	brook::bitmap obj(10000);
	std::set<int> flag;

	for (int i = 0; i < 5000; i++){
		int t = rand() % 10000;
		flag.insert(t);
		obj.set(t);
	}

	string * compressed = obj.Compress();

	brook::bitmap obj2(*compressed, 10000);
	for (set<int>::iterator iter = flag.begin(); iter != flag.end(); iter++)
		EXPECT_EQ(obj2.test(*iter), true);

	EXPECT_EQ(obj2.ListGen()->size(), flag.size());
	delete compressed;
}

TEST(BitMapTest, SpaceTest){
	const int base = 100000000;
	brook::bitmap obj(base);

	srand(time(NULL));
	for (int i = 0; i < base / 2; i++)
		obj.set(rand() % base);

	string * compressed = obj.Compress();


	cout << "The Compressed Content size is " << compressed->size() << endl;
	cout << "The Compression Ratio is " << (double)compressed->size() / (double)base  << endl;
	delete compressed;
}
