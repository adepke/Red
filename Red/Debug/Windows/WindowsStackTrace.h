/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include "../StackTraceBase.h"

#include <vector>

namespace Red
{
	bool CaptureStackTrace(int MaxDepth, std::vector<StackFrame>* Output);
}  // namespace Red