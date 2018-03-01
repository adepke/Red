#include "gtest/gtest.h"

#include "../../Red/Math/MathCore.h"

using namespace Red;

TEST(MathCoreSuite, AbsGeneralInt)
{
	EXPECT_EQ(3, Abs(3));
	EXPECT_EQ(3, Abs(-3));
	EXPECT_EQ(0, Abs(0));
}

TEST(MathCoreSuite, AbsGeneralFloat)
{
	EXPECT_FLOAT_EQ(3.0f, Abs(3.0f));
	EXPECT_FLOAT_EQ(3.0f, Abs(-3.0f));
	EXPECT_FLOAT_EQ(0.0f, Abs(0.0f));
}

TEST(MathCoreSuite, AbsGeneralDouble)
{
	EXPECT_EQ(3.0, Abs(3.0));
	EXPECT_EQ(3.0, Abs(-3.0));
	EXPECT_EQ(0.0, Abs(0.0));
}

TEST(MathCoreSuite, AbsGeneralLongDouble)
{
	EXPECT_EQ((long double)3.0, Abs((long double)3.0));
	EXPECT_EQ((long double)3.0, Abs((long double)-3.0));
	EXPECT_EQ((long double)0.0, Abs((long double)0.0));
}

TEST(MathCoreSuite, MinGeneral)
{
	EXPECT_EQ(3, Min(3, 3));
	EXPECT_EQ(-3, Min(-3, -3));
	EXPECT_EQ(-3, Min(3, -3));
	EXPECT_EQ(-3, Min(-3, 3));
	EXPECT_EQ(0, Min(0, 0));
}

TEST(MathCoreSuite, MaxGeneral)
{
	EXPECT_EQ(3, Max(3, 3));
	EXPECT_EQ(-3, Max(-3, -3));
	EXPECT_EQ(3, Max(3, -3));
	EXPECT_EQ(3, Max(-3, 3));
	EXPECT_EQ(0, Max(0, 0));
}

TEST(MathCoreSuite, PowerGeneral)
{
	EXPECT_EQ(64.0f, Power(4.0f, 3.0f));
	EXPECT_NEAR(104.47f, Power(7.23f, 2.35f), 0.01f);
	EXPECT_NEAR(80890.20, Power(26.21, 3.46), 0.01);
	EXPECT_NEAR((long double)340439729893056.21, Power((long double)53.45, (long double)8.41), 0.4);
}

TEST(MathCoreSuite, PowerSpecialCases)
{
	EXPECT_FLOAT_EQ(1.0f, Power(1.0f, 0.0f));
	EXPECT_FLOAT_EQ(0.0f, Power(0.0f, 1.0f));
	EXPECT_FLOAT_EQ(1.0f, Power(0.0f, 0.0f));
}

TEST(MathCoreSuite, SquareRootGeneral)
{
	EXPECT_EQ(0.0f, SquareRoot(0.0f));
	EXPECT_FLOAT_EQ(3.0f, SquareRoot(9.0f));
	EXPECT_NEAR(2.28, SquareRoot(5.20), 0.01);
	EXPECT_NEAR((long double)773.11, SquareRoot((long double)597695.0), 0.01);
}

TEST(MathCoreSuite, SquareRootNegative)
{
	EXPECT_NO_THROW(SquareRoot(-1.0f));
	EXPECT_NO_THROW(SquareRoot(-0.01f));
}