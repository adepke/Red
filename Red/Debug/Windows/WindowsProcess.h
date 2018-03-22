/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include "../ProcessBase.h"

#include <vector>

namespace Red
{
	bool GetProcessModules(std::vector<ProcessModule>* Output);
}  // namespace Red