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
	Mat.Data[0][1] = 0.01f;
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