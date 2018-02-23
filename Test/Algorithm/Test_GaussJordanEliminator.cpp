#include "gtest/gtest.h"

#include "../../Red/Algorithm/GaussJordanEliminator.h"

using namespace Red;

class CocktailShakerSortSuite : public ::testing::Test
{
protected:
	virtual void SetUp() override
	{
		for (int Row = 0; Row < 5; ++Row)
		{
			for (int Column = 0; Column < 5; ++Column)
			{
				Normal.Data[Row][Column] = Row - Column;
			}
		}

		for (int Row = 0; Row < 4; ++Row)
		{
			for (int Column = 0; Column < 4; ++Column)
			{
				Empty.Data[Row][Column] = 0.0f;
			}
		}

		OneByOneDimensions.Data[0][0] = 4.3f;
	}

	virtual void TearDown() override
	{
	}

	Matrix<5, 5> Normal;
	Matrix<4, 4> Empty;
	Matrix<1, 1> OneByOneDimensions;
};

TEST_F(CocktailShakerSortSuite, EmptyTarget)
{
	ASSERT_NO_THROW(Internal::CocktailShakerSort(Empty));
	for (int Row = 0; Row < 4; ++Row)
	{
		for (int Column = 0; Column < 4; ++Column)
		{
			EXPECT_EQ(0.0f, Empty.Data[Row][Column]);
		}
	}
}

TEST_F(CocktailShakerSortSuite, OneByOneDimension)
{
	ASSERT_NO_THROW(Internal::CocktailShakerSort(OneByOneDimensions));
	EXPECT_EQ(4.3f, OneByOneDimensions.Data[0][0]);
}

TEST(RowZeroCountSuite, General)
{
	Matrix<1, 5> Mat;
	Mat.Data[0][0] = 0.00f;
	Mat.Data[0][1] = 0.01f;
	Mat.Data[0][2] = 0.00f;
	Mat.Data[0][3] = 1.70f;
	Mat.Data[0][4] = 0.00f;

	EXPECT_EQ(1, Internal::RowZeroCount(Mat, 0));
}

TEST(RowZeroCountSuite, NoZeros)
{
	Matrix<1, 5> Mat;
	Mat.Data[0][0] = 4.20f;
	Mat.Data[0][1] = 0.01f;
	Mat.Data[0][2] = 1.05f;
	Mat.Data[0][3] = 1.70f;
	Mat.Data[0][4] = 2.00f;

	EXPECT_EQ(0, Internal::RowZeroCount(Mat, 0));
}

TEST(RowZeroCountSuite, AllZeros)
{
	Matrix<1, 5> Mat;
	Mat.Data[0][0] = 0.00f;
	Mat.Data[0][1] = 0.00f;
	Mat.Data[0][2] = 0.00f;
	Mat.Data[0][3] = 0.00f;
	Mat.Data[0][4] = 0.00f;

	EXPECT_EQ(5, Internal::RowZeroCount(Mat, 0));
}

TEST(SwapRowSuite, General)
{
	Matrix<2, 3> Mat;
	Mat.Data[0][0] = 4.2f;
	Mat.Data[0][1] = 6.6f;
	Mat.Data[0][2] = 1.0f;
	Mat.Data[1][0] = 0.0f;
	Mat.Data[1][1] = 6.1f;
	Mat.Data[1][2] = 0.2f;

	ASSERT_NO_THROW(Internal::SwapRow(Mat, 0, 1));
	EXPECT_EQ(0.0f, Mat.Data[0][0]);
	EXPECT_EQ(6.1f, Mat.Data[0][1]);
	EXPECT_EQ(0.2f, Mat.Data[0][2]);
	EXPECT_EQ(4.2f, Mat.Data[1][0]);
	EXPECT_EQ(6.6f, Mat.Data[1][1]);
	EXPECT_EQ(1.0f, Mat.Data[1][2]);
}

TEST(DivideRowSuite, General)
{
	Matrix<1, 5> Mat;
	Mat.Data[0][0] = 4.20f;
	Mat.Data[0][1] = 0.00f;
	Mat.Data[0][2] = 1.05f;
	Mat.Data[0][3] = 1.70f;
	Mat.Data[0][4] = 2.00f;

	ASSERT_NO_THROW(Internal::DivideRow(Mat, 0, 3.05f));
	EXPECT_NEAR(1.38f, Mat.Data[0][0], 0.01f);
	EXPECT_NEAR(0.00f, Mat.Data[0][1], 0.01f);
	EXPECT_NEAR(0.34f, Mat.Data[0][2], 0.01f);
	EXPECT_NEAR(0.56f, Mat.Data[0][3], 0.01f);
	EXPECT_NEAR(0.66f, Mat.Data[0][4], 0.01f);
}

TEST(MultiplyRowCopySuite, General)
{
	Matrix<1, 5> Mat;
	Mat.Data[0][0] = 4.20f;
	Mat.Data[0][1] = 0.00f;
	Mat.Data[0][2] = 1.05f;
	Mat.Data[0][3] = 1.70f;
	Mat.Data[0][4] = 2.00f;

	float Result[5];

	ASSERT_NO_THROW(Internal::MultiplyRowCopy(Mat, Result, 0, 3.05f));
	EXPECT_NEAR(12.81f, Result[0], 0.01f);
	EXPECT_NEAR(0.00f, Result[1], 0.01f);
	EXPECT_NEAR(3.20f, Result[2], 0.01f);
	EXPECT_NEAR(5.19f, Result[3], 0.01f);
	EXPECT_NEAR(6.10f, Result[4], 0.01f);
}

class RowEchelonSuite : public ::testing::Test
{
protected:
	virtual void SetUp() override
	{
		Normal.Data[0][0] = 0.0f;
		Normal.Data[0][1] = 3.0f;
		Normal.Data[0][2] = -6.0f;
		Normal.Data[0][3] = 6.0f;
		Normal.Data[0][4] = 4.0f;
		Normal.Data[0][5] = -5.0f;
		Normal.Data[1][0] = 3.0f;
		Normal.Data[1][1] = -7.0f;
		Normal.Data[1][2] = 8.0f;
		Normal.Data[1][3] = -5.0f;
		Normal.Data[1][4] = 8.0f;
		Normal.Data[1][5] = 9.0f;
		Normal.Data[2][0] = 3.0f;
		Normal.Data[2][1] = -9.0f;
		Normal.Data[2][2] = 12.0f;
		Normal.Data[2][3] = -9.0f;
		Normal.Data[2][4] = 6.0f;
		Normal.Data[2][5] = 15.0f;
	}

	virtual void TearDown() override
	{
	}

	Matrix<3, 6> Normal;
};

TEST_F(RowEchelonSuite, General)
{
	Matrix<3, 6> Result;

	Result = RowEchelon(Normal);

	EXPECT_FLOAT_EQ(1.0f, Result.Data[0][0]);
	EXPECT_NEAR(-2.33f, Result.Data[0][1], 0.01f);
	EXPECT_NEAR(2.67f, Result.Data[0][2], 0.01f);
	EXPECT_NEAR(-1.67f, Result.Data[0][3], 0.01f);
	EXPECT_NEAR(2.67f, Result.Data[0][4], 0.01f);
	EXPECT_FLOAT_EQ(3.0f, Result.Data[0][5]);
	EXPECT_FLOAT_EQ(0.0f, Result.Data[1][0]);
	EXPECT_FLOAT_EQ(1.0f, Result.Data[1][1]);
	EXPECT_FLOAT_EQ(-2.0f, Result.Data[1][2]);
	EXPECT_FLOAT_EQ(2.0f, Result.Data[1][3]);
	EXPECT_FLOAT_EQ(1.0f, Result.Data[1][4]);
	EXPECT_FLOAT_EQ(-3.0f, Result.Data[1][5]);
	EXPECT_FLOAT_EQ(0.0f, Result.Data[2][0]);
	EXPECT_FLOAT_EQ(0.0f, Result.Data[2][1]);
	EXPECT_FLOAT_EQ(0.0f, Result.Data[2][2]);
	EXPECT_FLOAT_EQ(0.0f, Result.Data[2][3]);
	EXPECT_FLOAT_EQ(1.0f, Result.Data[2][4]);
	EXPECT_FLOAT_EQ(4.0f, Result.Data[2][5]);
}

TEST_F(RowEchelonSuite, ReducedGeneral)
{
	Matrix<3, 6> Result;

	Result = ReducedRowEchelon(Normal);

	EXPECT_FLOAT_EQ(1.0f, Result.Data[0][0]);
	EXPECT_FLOAT_EQ(0.0f, Result.Data[0][1]);
	EXPECT_FLOAT_EQ(-2.0f, Result.Data[0][2]);
	EXPECT_FLOAT_EQ(3.0f, Result.Data[0][3]);
	EXPECT_FLOAT_EQ(0.0f, Result.Data[0][4]);
	EXPECT_FLOAT_EQ(-24.0f, Result.Data[0][5]);
	EXPECT_FLOAT_EQ(0.0f, Result.Data[1][0]);
	EXPECT_FLOAT_EQ(1.0f, Result.Data[1][1]);
	EXPECT_FLOAT_EQ(-2.0f, Result.Data[1][2]);
	EXPECT_FLOAT_EQ(2.0f, Result.Data[1][3]);
	EXPECT_FLOAT_EQ(0.0f, Result.Data[1][4]);
	EXPECT_FLOAT_EQ(-7.0f, Result.Data[1][5]);
	EXPECT_FLOAT_EQ(0.0f, Result.Data[2][0]);
	EXPECT_FLOAT_EQ(0.0f, Result.Data[2][1]);
	EXPECT_FLOAT_EQ(0.0f, Result.Data[2][2]);
	EXPECT_FLOAT_EQ(0.0f, Result.Data[2][3]);
	EXPECT_FLOAT_EQ(1.0f, Result.Data[2][4]);
	EXPECT_FLOAT_EQ(4.0f, Result.Data[2][5]);
}