/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#include "WindowsStackTrace.h"

#include "../../Math/MathCore.h"

#include <Windows.h>
#include <DbgHelp.h>
#include <utility>

namespace Red
{
	void Initialize()
	{
		SymInitialize(GetCurrentProcess(), nullptr, true);
	}

	bool CaptureStackTrace(int MaxDepth, std::vector<StackFrame>* Output)
	{
		if (!Output || MaxDepth <= 0)
		{
			return false;
		}

		Initialize();

		short int Frames = 0;
		PVOID RawStackTrace[128];

		// Requires Frame Pointer Omission (/Oy)
		Frames = RtlCaptureStackBackTrace(0, Min(MaxDepth, 128), RawStackTrace, NULL);

		if (Frames <= 0)
		{
			return false;
		}

		for (short int Iter = 0; Iter < Frames; ++Iter)
		{
			ULONG64 FrameDWORD64 = (ULONG64)RawStackTrace[Iter];
			HANDLE Process = GetCurrentProcess();

			StackFrame Frame;

			char FrameAddressBuffer[64];
			snprintf(FrameAddressBuffer, sizeof(FrameAddressBuffer), "0x%016X", static_cast<unsigned int>(FrameDWORD64));

			Frame.Address = FrameAddressBuffer;

			char FrameBuffer[sizeof(IMAGEHLP_SYMBOL64) + 1024] = { 0 };

			IMAGEHLP_SYMBOL64* FrameBufferSymbol = (IMAGEHLP_SYMBOL64*)FrameBuffer;
			FrameBufferSymbol->SizeOfStruct = sizeof(FrameBuffer);
			FrameBufferSymbol->MaxNameLength = 1024;

			if (SymGetSymFromAddr64(Process, FrameDWORD64, nullptr, FrameBufferSymbol))
			{
				Frame.Function = FrameBufferSymbol->Name;
			}

			IMAGEHLP_MODULE64 FrameBufferModule = { 0 };
			FrameBufferModule.SizeOfStruct = sizeof(FrameBufferModule);

			if (SymGetModuleInfo64(Process, FrameDWORD64, &FrameBufferModule))
			{
				Frame.Module = FrameBufferModule.ModuleName;
			}

			IMAGEHLP_LINE64 FrameBufferFileLine = { 0 };
			FrameBufferFileLine.SizeOfStruct = sizeof(FrameBufferFileLine);

			DWORD Displacement;
			if (SymGetLineFromAddr64(Process, FrameDWORD64, &Displacement, &FrameBufferFileLine))
			{
				Frame.File = FrameBufferFileLine.FileName;
				Frame.Line = std::to_string(FrameBufferFileLine.LineNumber);
			}

			Output->push_back(Frame);
		}

		return true;
	}
}  // namespace Red