/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include "../Core/Platform.h"

#include <string>
#include <array>
#include <stdexcept>
#include <memory>

// Execute Command Through Shell
std::string ShellExec(const char* Command)
{
	std::array<char, 128> Buffer;
	std::string Result;

#if OS_WINDOWS
	FILE* Pipe = _popen(Command, "r");
#else
	FILE* Pipe = popen(Command, "r");
#endif
	if (!Pipe)
	{
		throw std::runtime_error("Failed to Create Shell Command Pipe");
	}

	while (!feof(Pipe))
	{
		if (fgets(Buffer.data(), 128, Pipe))
		{
			Result += Buffer.data();
		}
	}

#if OS_WINDOWS
	_pclose(Pipe);
#else
	pclose(Pipe);
#endif
	
	return Result;
}