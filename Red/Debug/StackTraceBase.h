/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include <string>

namespace Red
{
	struct StackFrame
	{
		unsigned int Address;
		std::string File;
		std::string Function;
		std::string Line;
	};
}  // namespace Red