#include "Function.h"

#include <functional>
#include <iostream>
#include <chrono>

// Sample Function
int SomeFunction(bool SomeParam)
{
	return (SomeParam ? 1 : 0);
}

int main()
{
	using namespace Red::Function;

	// Sample Lambda
	int MyInt = 3;
	auto MyLambda = [&MyInt](bool SomeParam) -> int
	{
		return (SomeParam ? 0 : 1) + MyInt;
	};

	// Some Demo Instantiations
	Function<int(bool)> MyFunctionPtrObj(&SomeFunction);
	Function<int(bool)> MyFunctionPtrObj2 = &SomeFunction;
	Function<int(bool)> MyLambdaObj(MyLambda);
	Function<int(bool)> MyLambdaObj2 = MyLambda;

	// Some Demo Calls
	MyFunctionPtrObj(false);
	MyFunctionPtrObj2(true);
	MyLambdaObj(false);
	MyLambdaObj2(true);

	// Sizes of Each Object
	std::cout << "Sizeof Red::Function::Delegate: " << sizeof(Delegate<UClass, int, bool>) << std::endl;
	std::cout << "Sizeof Red::Function::Function: " << sizeof(Function<int(bool)>) << std::endl;
	std::cout << "Sizeof Std::Function: " << sizeof(std::function<int(bool)>) << std::endl;

	// Execution Time of 500000 Calls to Red::Function::Function
	auto Start1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 500000; ++i)
		MyFunctionPtrObj(true);
	auto End1 = std::chrono::high_resolution_clock::now();
	std::cout << "Call Time (500k Executions) | Red::Function: " << std::chrono::duration_cast<std::chrono::milliseconds>(End1 - Start1).count() << "ms" << std::endl;

	// Creating Same Function Type in Std::Function
	std::function<int(bool)> MyStdFunc = &SomeFunction;

	// Execution Time of 500000 Calls to Std::Function
	auto Start2 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 500000; ++i)
		MyStdFunc(true);
	auto End2 = std::chrono::high_resolution_clock::now();
	std::cout << "Call Time (50k Executions) | Std::Function: " << std::chrono::duration_cast<std::chrono::milliseconds>(End2 - Start2).count() << "ms" << std::endl;

	system("pause");

	return 0;
}