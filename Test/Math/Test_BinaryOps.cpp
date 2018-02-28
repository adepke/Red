#include "gtest/gtest.h"

#include "../../Red/Math/BinaryOps.h"

#include "../../Red/Core/Platform.h"

using namespace Red;

TEST(BinaryOpsSuite, BitReadSigned)
{
	// Big Endian: 00011111011001100001011110111010

#if PLATFORM_BIGENDIAN
	uint32_t Sample = 526784442;
#else
	uint32_t Sample = 1575511800;
#endif

	EXPECT_EQ(0, BitRead(Sample, 0));
	EXPECT_EQ(0, BitRead(Sample, 1));
	EXPECT_EQ(1, BitRead(Sample, 10));
	EXPECT_EQ(0, BitRead(Sample, 31));
}

TEST(BinaryOpsSuite, BitReadUnsigned)
{
	// Big Endian: 10011111011001100001011110111010

#if PLATFORM_BIGENDIAN
	int32_t Sample = -1620699206;
#else
	int32_t Sample = 1575511801;
#endif

	EXPECT_EQ(1, BitRead(Sample, 0));
	EXPECT_EQ(0, BitRead(Sample, 1));
	EXPECT_EQ(1, BitRead(Sample, 10));
	EXPECT_EQ(0, BitRead(Sample, 31));
}

TEST(BinaryOpsSuite, BitWriteSigned)
{
	// Big Endian: 00011111011001100001011110111010

#if PLATFORM_BIGENDIAN
	uint32_t Sample = 526784442;
#else
	uint32_t Sample = 1575511800;
#endif

	// Big Endian: 01111111010001100001011110111101

#if PLATFORM_BIGENDIAN
	uint32_t Expected = 2135300029;
#else
	uint32_t Expected = 3186123518;
#endif

	ASSERT_NO_THROW(BitWrite(Sample, 0, 0));
	ASSERT_NO_THROW(BitWrite(Sample, 1, 1));
	ASSERT_NO_THROW(BitWrite(Sample, 2, 1));
	ASSERT_NO_THROW(BitWrite(Sample, 10, 0));
	ASSERT_NO_THROW(BitWrite(Sample, 29, 1));
	ASSERT_NO_THROW(BitWrite(Sample, 30, 0));
	ASSERT_NO_THROW(BitWrite(Sample, 31, 1));

	EXPECT_EQ(Expected, Sample);
}

TEST(BinaryOpsSuite, BitWriteUnsigned)
{
	// Big Endian: 10011111011001100001011110111010

#if PLATFORM_BIGENDIAN
	int32_t Sample = -1620699206;
#else
	int32_t Sample = 1575511801;
#endif

	// Big Endian: 01111111010001100001011110111101

#if PLATFORM_BIGENDIAN
	int32_t Expected = 2135300029;
#else
	int32_t Expected = -1108843778;
#endif

	ASSERT_NO_THROW(BitWrite(Sample, 0, 0));
	ASSERT_NO_THROW(BitWrite(Sample, 1, 1));
	ASSERT_NO_THROW(BitWrite(Sample, 2, 1));
	ASSERT_NO_THROW(BitWrite(Sample, 10, 0));
	ASSERT_NO_THROW(BitWrite(Sample, 29, 1));
	ASSERT_NO_THROW(BitWrite(Sample, 30, 0));
	ASSERT_NO_THROW(BitWrite(Sample, 31, 1));

	EXPECT_EQ(Expected, Sample);
}

TEST(BinaryOpsSuite, BitFlipSigned)
{
	// Big Endian: 00011111011001100001011110111010

#if PLATFORM_BIGENDIAN
	uint32_t Sample = 526784442;
#else
	uint32_t Sample = 1575511800;
#endif

	// Big Endian: 11011111010001100001011110111011

#if PLATFORM_BIGENDIAN
	uint32_t Expected = 3745912763;
#else
	uint32_t Expected = 3722994427;
#endif

	ASSERT_NO_THROW(BitFlip(Sample, 0));
	ASSERT_NO_THROW(BitFlip(Sample, 1));
	ASSERT_NO_THROW(BitFlip(Sample, 10));
	ASSERT_NO_THROW(BitFlip(Sample, 31));

	EXPECT_EQ(Expected, Sample);
}

TEST(BinaryOpsSuite, BitFlipUnsigned)
{
	// Big Endian: 10011111011001100001011110111010

#if PLATFORM_BIGENDIAN
	int32_t Sample = -1620699206;
#else
	int32_t Sample = 1575511801;
#endif

	// Big Endian: 01011111010001100001011110111011

#if PLATFORM_BIGENDIAN
	uint32_t Expected = 1598429115;
#else
	uint32_t Expected = -571972870;
#endif

	ASSERT_NO_THROW(BitFlip(Sample, 0));
	ASSERT_NO_THROW(BitFlip(Sample, 1));
	ASSERT_NO_THROW(BitFlip(Sample, 10));
	ASSERT_NO_THROW(BitFlip(Sample, 31));

	EXPECT_EQ(Expected, Sample);
}