#include "stack.h"
#include "gtest/gtest.h"

// The fixture for testing class
class StackTest: public ::testing::Test
{
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	StackTest()
	{
		// You can do set-up work for each test here.
	}

	virtual ~StackTest()
	{
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	virtual void SetUp()
	{
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown()
	{
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests
	stack<int> s;
};

TEST_F(StackTest, OnePushPop)
{
    ASSERT_TRUE(s.isEmpty());
    s.push(1);
    EXPECT_EQ(1, s.top());
    s.pop();
    ASSERT_TRUE(s.isEmpty());
}

TEST_F(StackTest, Scale)
{
	// Exercises the Xyz feature of Foo.
}

