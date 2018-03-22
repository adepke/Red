/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include <string>

namespace Red
{
	struct StackFrame
	{
		std::string Address;
		std::string Module;
		std::string File;
		std::string Function;
		std::string Line;
	};
}  // namespace Red