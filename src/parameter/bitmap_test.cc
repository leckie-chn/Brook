// Copyright 2015 PKU-Cloud
// Author Yan Ni(leckie.dove@gmail.com)

#include <gtest/gtest.h>
#include <src/parameter/bitmap.h>

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
