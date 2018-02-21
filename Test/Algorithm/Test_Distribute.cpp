#include "gtest/gtest.h"

#include "../../Red/Algorithm/Distribute.h"

TEST(DistributeSuite, NoRemainder)
{
	int* Return = new int[5];

	ASSERT_NO_THROW(Red::Distribute(Return, 25, 5));
	for (int Iter = 0; Iter < 5; ++Iter)
	{
		EXPECT_EQ(5, Return[Iter]);
	}

	delete[] Return;

	std::vector<int> ReturnVector;

	ASSERT_NO_THROW(Red::Distribute(&ReturnVector, 25, 5));
	EXPECT_EQ(5, ReturnVector.size());
	for (auto& Element : ReturnVector)
	{
		EXPECT_EQ(5, Element);
	}
}

TEST(DistributeSuite, Remainder)
{
	int* Return = new int[5];

	ASSERT_NO_THROW(Red::Distribute(Return, 21, 5));
	for (int Iter = 0; Iter < 4; ++Iter)
	{
		EXPECT_EQ(4, Return[Iter]);
	}
	EXPECT_EQ(5, Return[4]);

	delete[] Return;

	std::vector<int> ReturnVector;

	ASSERT_NO_THROW(Red::Distribute(&ReturnVector, 21, 5));
	EXPECT_EQ(5, ReturnVector.size());
	for (int Iter = 0; Iter < ReturnVector.size() - 1; ++Iter)
	{
		EXPECT_EQ(4, ReturnVector[Iter]);
	}
	EXPECT_EQ(5, ReturnVector[4]);
}

TEST(DistributeSuite, RemainderDropped)
{
	int* Return = new int[5];

	ASSERT_NO_THROW(Red::Distribute(Return, 21, 5, false));
	for (int Iter = 0; Iter < 5; ++Iter)
	{
		EXPECT_EQ(4, Return[Iter]);
	}

	delete[] Return;
	
	std::vector<int> ReturnVector;

	ASSERT_NO_THROW(Red::Distribute(&ReturnVector, 21, 5, false));
	EXPECT_EQ(5, ReturnVector.size());
	for (auto& Element : ReturnVector)
	{
		EXPECT_EQ(4, Element);
	}
}

TEST(DistributeSuite, NullDestination)
{
	int* Return = nullptr;

	ASSERT_NO_THROW(Red::Distribute(Return, 10, 5));
}

TEST(DistributeSuite, TotalZero)
{
	int* Return = new int;

	ASSERT_NO_THROW(Red::Distribute(Return, 0, 5));
	EXPECT_EQ(0, *Return);

	delete Return;

	std::vector<int> ReturnVector;

	ASSERT_NO_THROW(Red::Distribute(&ReturnVector, 0, 5));
	EXPECT_EQ(1, ReturnVector.size());
}

TEST(DistributeSuite, ChunkCountZero)
{
	int* Return = new int;

	ASSERT_NO_THROW(Red::Distribute(Return, 10, 0));
	EXPECT_EQ(0, *Return);

	delete Return;

	std::vector<int> ReturnVector;

	ASSERT_NO_THROW(Red::Distribute(&ReturnVector, 10, 0));
	EXPECT_EQ(1, ReturnVector.size());
}

TEST(DistributeSuite, MoreChunksThanTotalAsInteger)
{
	int* Return = new int;

	ASSERT_NO_THROW(Red::Distribute(Return, 5, 10));
	EXPECT_EQ(0, *Return);

	delete Return;

	std::vector<int> ReturnVector;

	ASSERT_NO_THROW(Red::Distribute(&ReturnVector, 5, 10));
	EXPECT_EQ(1, ReturnVector.size());
	EXPECT_EQ(0, ReturnVector[0]);
}

TEST(DistributeSuite, MoreChunksThanTotalAsFloat)
{
	float* Return = new float[10];

	ASSERT_NO_THROW(Red::Distribute(Return, 5.0f, 10));
	for (int Iter = 0; Iter < 10; ++Iter)
	{
		EXPECT_EQ(0.5, Return[Iter]);
	}

	delete[] Return;

	std::vector<float> ReturnVector;

	ASSERT_NO_THROW(Red::Distribute(&ReturnVector, 5.0f, 10));
	for (auto& Element : ReturnVector)
	{
		EXPECT_EQ(0.5, Element);
	}
}