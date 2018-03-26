/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#include "LinuxStackTrace.h"

#include "../../Math/MathCore.h"

#include <cxxabi.h>
#include <execinfo.h>
#include <dlfcn.h>

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

			// Note: Module Name Can Also Be Obtained From dladdr()
			size_t ModuleNameEnd = FrameString.find('(');
			Frame.Module = FrameString.substr(0, ModuleNameEnd);
			
			// Isolate the Module Name in the Case of "./<ModuleName>"
			if (sizeof(Frame.Module) / sizeof(Frame.Module[0]) > 2)
			{
				if (Frame.Module[0] == '.' && Frame.Module[1] == '/')
				{
					Frame.Module = Frame.Module.substr(2);
				}
			}

			Dl_info Info;

			if (dladdr(RawStackTrace[Iter], &Info) && Info.dli_sname)
			{
				int OperationStatus;

				char* DemangledName = abi::__cxa_demangle(Info.dli_sname, nullptr, 0, &OperationStatus);

				if (OperationStatus == 0 && DemangledName)
				{
					Frame.Function = DemangledName;

					free(DemangledName);
				}

				else
				{
					Frame.Function == Info.dli_sname;
				}
			}
			
			Output->push_back(Frame);
		}

		if (StackTrace)
		{
			free(StackTrace);
		}

		return true;
	}
}  // namespace Red
