/**
 * @file
 * @author Yan Ni <leckie.dove@gmail.com>
 *
 * @section description
 * Testing code for SkipList
 */

#include "src/parameter/skip_list_tmpl.h"
#include "src/parameter/random_queue_tmpl.h"

#include <gtest/gtest.h>

#include <cstdlib>
#include <ctime>
#include <climits>

TEST(SkipListTest, SimpleTest){
	brook::SkipListQueue<int> q0;

	for (int i = 0; i < 9; i++)
		q0.push(i);

	for (int i = 0; i < 9; i++)
		EXPECT_EQ(q0.get(i), i);

	EXPECT_EQ(q0.size(), 9);

	for (int i = 0; i < 9; i++)
		EXPECT_EQ(q0.pop(), i);

	EXPECT_EQ(q0.size(), 0);
}

TEST(SkipListTest, RandomTest){
	brook::SkipListQueue<int> q0;
	brook::RandomQueueTmpl<int> q1;

	srand(time(NULL));

	for (int i = 0; i < 256; i++){
		int t = rand() % INT_MAX;
		q0.push(t);
		q1.Push(t);
	}

	for (int i = 0; i < 256; i++){
		int op = rand() % INT_MAX;
		if (op == 0){
			int t = rand() % INT_MAX;
			q0.push(t);
			q1.Push(t);
		} else
			EXPECT_EQ(q0.pop(), q1.Pop());
	}

	EXPECT_EQ(q1.Size(), q0.size());

	for (int i = 0; i < q0.size(); i++){
		EXPECT_EQ(q0.get(i), q1.Get(i));
	}

}
