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
