#include "gtest/gtest.h"

#include "../../Red/Math/AABB.h"

using namespace Red;

class AABBSuite : public ::testing::Test
{
protected:
	virtual void SetUp() override
	{
		NormalA.Location = Vector3(8.0f, -2.0f, 5.0f);
		NormalA.HalfSize = Vector3(2.0f, 6.0f, -1.0f);

		NormalB.Location = Vector3(1.0f, 0.0f, 1.0f);
		NormalB.HalfSize = Vector3(-7.0f, -6.0f, 0.0f);
	}

	virtual void TearDown() override
	{
	}

	AABB NormalA;
	AABB NormalB;
};

TEST_F(AABBSuite, GeneralFunctions)
{
	EXPECT_EQ(Vector3(6.0f, -8.0f, 4.0f), NormalA.Minimum());
	EXPECT_EQ(Vector3(10.0f, 4.0f, 6.0f), NormalA.Maximum());
	EXPECT_FLOAT_EQ(-96.0f, NormalA.Volume());
}

TEST_F(AABBSuite, OperatorAssignment)
{
	ASSERT_NO_THROW(NormalA = NormalB);
	EXPECT_EQ(NormalB.Location, NormalA.Location);
	EXPECT_EQ(NormalB.HalfSize, NormalA.HalfSize);

	ASSERT_NO_THROW(NormalA = Vector3(0.0f, 1.0f, -3.0f));
	EXPECT_EQ(Vector3(0.0f, 1.0f, -3.0f), NormalA.Location);
	EXPECT_EQ(NormalB.HalfSize, NormalA.HalfSize);
}

TEST_F(AABBSuite, OperatorAddition)
{
	AABB Sample;

	ASSERT_NO_THROW(Sample = NormalA + NormalB);
	EXPECT_EQ(Vector3(9.0f, -2.0f, 6.0f), Sample.Location);
	EXPECT_EQ(Vector3(-5.0f, 0.0f, -1.0f), Sample.HalfSize);

	ASSERT_NO_THROW(Sample = NormalA + Vector3(4.0f, -2.0f, 9.0f));
	EXPECT_EQ(Vector3(12.0f, -4.0f, 14.0f), Sample.Location);
	EXPECT_EQ(NormalA.HalfSize, Sample.HalfSize);

	ASSERT_NO_THROW(NormalA += NormalB);
	EXPECT_EQ(Vector3(9.0f, -2.0f, 6.0f), NormalA.Location);
	EXPECT_EQ(Vector3(-5.0f, 0.0f, -1.0f), NormalA.HalfSize);

	ASSERT_NO_THROW(NormalA += Vector3(4.0f, -2.0f, 9.0f));
	EXPECT_EQ(Vector3(13.0f, -4.0f, 15.0f), NormalA.Location);
	EXPECT_EQ(Vector3(-5.0f, 0.0f, -1.0f), NormalA.HalfSize);
}

TEST_F(AABBSuite, OperatorSubtraction)
{
	AABB Sample;

	ASSERT_NO_THROW(Sample = NormalA - NormalB);
	EXPECT_EQ(Vector3(7.0f, -2.0f, 4.0f), Sample.Location);
	EXPECT_EQ(Vector3(9.0f, 12.0f, -1.0f), Sample.HalfSize);

	ASSERT_NO_THROW(Sample = NormalA - Vector3(4.0f, -2.0f, 9.0f));
	EXPECT_EQ(Vector3(4.0f, 0.0f, -4.0f), Sample.Location);
	EXPECT_EQ(NormalA.HalfSize, Sample.HalfSize);

	ASSERT_NO_THROW(NormalA -= NormalB);
	EXPECT_EQ(Vector3(7.0f, -2.0f, 4.0f), NormalA.Location);
	EXPECT_EQ(Vector3(9.0f, 12.0f, -1.0f), NormalA.HalfSize);

	ASSERT_NO_THROW(NormalA -= Vector3(4.0f, -2.0f, 9.0f));
	EXPECT_EQ(Vector3(3.0f, 0.0f, -5.0f), NormalA.Location);
	EXPECT_EQ(Vector3(9.0f, 12.0f, -1.0f), NormalA.HalfSize);
}

TEST_F(AABBSuite, OperatorIncrement)
{
	ASSERT_NO_THROW(++NormalA);
	EXPECT_EQ(Vector3(8.0f, -2.0f, 5.0f), NormalA.Location);
	EXPECT_EQ(Vector3(3.0f, 7.0f, 0.0f), NormalA.HalfSize);
}

TEST_F(AABBSuite, OperatorDecrement)
{
	ASSERT_NO_THROW(--NormalA);
	EXPECT_EQ(Vector3(8.0f, -2.0f, 5.0f), NormalA.Location);
	EXPECT_EQ(Vector3(1.0f, 5.0f, -2.0f), NormalA.HalfSize);
}

TEST_F(AABBSuite, OperatorLogical)
{
	EXPECT_FALSE(NormalA == NormalB);
	EXPECT_TRUE(NormalA != NormalB);
}