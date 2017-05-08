#include "../Function/Function.h"

#include <functional>
#include <iostream>
#include <chrono>

// Sample Function
int SomeFunction(bool SomeParam)
{
	return (SomeParam ? 1 : 0);
}

class SomeClass {};

int main()
{
	using namespace Red::Function;

	// Sample Variables
	int MyInt = 3;
	bool MyBool = false;

	// Sample Lambda
	auto MyLambda = [&MyInt](bool SomeParam, int& SomeParamRef) -> int
	{
		return (SomeParam ? 0 : 1) + MyInt - SomeParamRef;
	};

	// Some Demo Instantiations
	Function<int(bool)> DemoFunctionPointer(&SomeFunction);
	Function<int(bool, int&)> DemoLambda(MyLambda);

	// Some Demo Calls
	DemoFunctionPointer(true);
	//DemoFunctionPointer(SomeParam1);  // DemoFunctionPointer Must Be <int(bool&)> For This!
	DemoLambda(false, MyInt);

	// Sizes of Each Object
	std::cout << "Sizeof Red::Function::Delegate: " << sizeof(Delegate<SomeClass, void>) << std::endl;
	std::cout << "Sizeof Red::Function::Function: " << sizeof(Function<void()>) << std::endl;
	std::cout << "Sizeof Std::Function:           " << sizeof(std::function<void()>) << std::endl;



	system("pause");

	return 0;



	// Execution Time of 500000 Calls to Red::Function::Function
	auto Start1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 500000000; ++i)
		DemoFunctionPointer(true);
	auto End1 = std::chrono::high_resolution_clock::now();
	std::cout << "Call Time (500 Million Executions) | Red::Function: " << std::chrono::duration_cast<std::chrono::milliseconds>(End1 - Start1).count() << "ms" << std::endl;

	// Creating Same Function Type in Std::Function
	std::function<int(bool)> DemoStdFunc = &SomeFunction;

	// Execution Time of 500000 Calls to Std::Function
	auto Start2 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 500000000; ++i)
		DemoStdFunc(true);
	auto End2 = std::chrono::high_resolution_clock::now();
	std::cout << "Call Time (500 Million Executions) | Std::Function: " << std::chrono::duration_cast<std::chrono::milliseconds>(End2 - Start2).count() << "ms" << std::endl;

	system("pause");

	return 0;
}