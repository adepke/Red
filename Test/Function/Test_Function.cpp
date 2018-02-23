#include "gtest/gtest.h"

#include "../../Red/Function/Function.h"

using namespace Red;

int TestFunction(int Value)
{
	return Value - 2;
}

TEST(FunctionSuite, FunctionPointerConstruction)
{
	Function<int(int)> Func(&TestFunction);

	EXPECT_EQ(0, Func(2));
}

TEST(FunctionSuite, FunctionPointerAssignment)
{
	Function<int(int)> Func = &TestFunction;

	EXPECT_EQ(1, Func(3));
}

TEST(FunctionSuite, LambaConstruction)
{
	Function<int(int)> Func([&](int Value) { return TestFunction(Value); });

	EXPECT_EQ(2, Func(4));
}

TEST(FunctionSuite, LambaAssignment)
{
	int Result = 0;

	Function<int(int)> Func = [&](int Value) { return TestFunction(Value); };

	EXPECT_EQ(3, Func(5));
}

class DummyClass
{
private:
	int Value = 6;

public:
	int GetValue() { return Value; }
};

class DelegateSuite : public ::testing::Test
{
protected:
	virtual void SetUp() override
	{
		Dummy = new DummyClass();
	}

	virtual void TearDown() override
	{
		delete Dummy;
	}

	DummyClass* Dummy;
};

TEST_F(DelegateSuite, MemberFunctionPointerConstruction)
{
	Delegate<DummyClass, int()> Del(*Dummy, &Dummy::GetValue);

	EXPECT_EQ(6, Del());
}