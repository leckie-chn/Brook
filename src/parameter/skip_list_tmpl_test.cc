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

using namespace brook;

typedef SkipListQueueTmpl<int> SkipListQueue;
typedef RandomQueueTmpl<int> RandomQueue;

TEST(SkipListTest, SimpleTest){
	SkipListQueue q0;

	for (int i = 0; i < 9; i++)
		q0.Push(i);

	for (int i = 0; i < 9; i++)
		EXPECT_EQ(q0.Get(i), i);

	EXPECT_EQ(q0.Size(), 9);

	for (int i = 0; i < 9; i++)
		EXPECT_EQ(q0.Pop(), i);

	EXPECT_EQ(q0.Size(), 0);
}

TEST(SkipListTest, RandomTest){
	SkipListQueue q0;
	RandomQueue q1;

	srand(time(NULL));

	for (int i = 0; i < 256; i++){
		int t = rand() % INT_MAX;
		q0.Push(t);
		q1.Push(t);
	}

	for (int i = 0; i < 256; i++){
		int op = rand() % INT_MAX;
		if (op == 0){
			int t = rand() % INT_MAX;
			q0.Push(t);
			q1.Push(t);
		} else
			EXPECT_EQ(q0.Pop(), q1.Pop());
	}

	EXPECT_EQ(q1.Size(), q0.Size());

	for (int i = 0; i < q0.Size(); i++){
		EXPECT_EQ(q0.Get(i), q1.Get(i));
	}

}
