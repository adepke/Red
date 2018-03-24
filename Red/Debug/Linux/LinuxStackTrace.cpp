/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#include "LinuxStackTrace.h"

#include "../../Math/MathCore.h"

#include <cxxabi.h>
#include <execinfo.h>

#include <stdlib.h>  // Darwin Doesn't Have free() By Default, Include it Here

namespace Red
{
	bool CaptureStackTrace(int MaxDepth, std::vector<StackFrame>* Output)
	{
		if (!Output || MaxDepth <= 0)
		{
			return false;
		}

		size_t Frames = 0;
		void* RawStackTrace[128];

		Frames = backtrace(RawStackTrace, Min(MaxDepth, 128));

		if (Frames <= 0)
		{
			return false;
		}

		char** StackTrace = backtrace_symbols(RawStackTrace, Frames);

		for (size_t Iter = 0; Iter < Frames; ++Iter)
		{
			std::string FrameString = StackTrace[Iter];

			StackFrame Frame;

			char FrameAddressBuffer[64];
			snprintf(FrameAddressBuffer, sizeof(FrameAddressBuffer), "0x%016llX", (unsigned long long int)RawStackTrace[Iter]);  // Assume 64 Bit Addresses.

			Frame.Address = FrameAddressBuffer;

			size_t ModuleNameEnd = FrameString.find('(');
			Frame.Module = FrameString.substr(0, ModuleNameEnd);

			size_t FunctionNameStart = FrameString.find('(') + 1;
			size_t FunctionNameEnd = FrameString.find("+0x") - 1;

			// Don't Try to Demangle if There's No Function Signature. Note: std::string::npos Wasn't Working on Ubuntu Linux With gcc
			if (FunctionNameEnd > 1024)
			{
				int OperationStatus = 0;

				char* DemangledName = abi::__cxa_demangle(FrameString.substr(FunctionNameStart, FunctionNameEnd - FunctionNameStart).c_str(), nullptr, nullptr, &OperationStatus);
			
				if (OperationStatus == 0)
				{
					Frame.Function = DemangledName;

					free(DemangledName);
				}

				else
				{
					Frame.Function = FrameString.substr(FunctionNameStart, FunctionNameEnd - FunctionNameStart);
				}
			}
			
			else
			{
				Frame.Function = "";
			}
			
			Output->push_back(Frame);
		}

		return true;
	}
}  // namespace Red
