/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#include "LinuxStackTrace.h"

#include "../../Math/MathCore.h"

#include <cxxabi.h>
#include <execinfo.h>

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

			size_t ModuleNameEnd = FrameString.find('(') - 1;
			Frame.Module = FrameString.substr(0, ModuleNameEnd);

			size_t FunctionNameStart = FrameString.find('(') + 1;
			size_t FunctionNameEnd = FrameString.find('+') - 1;

#ifdef HAVE_CXA_DEMANGLE
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
#else
			Frame.Function = FrameString.substr(FunctionNameStart, FunctionNameEnd - FunctionNameStart);
#endif
		}

		return true;
	}
}  // namespace Red
