/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#include "WindowsProcess.h"

#include <Windows.h>
#include <Psapi.h>

namespace Red
{
	bool GetProcessModules(std::vector<ProcessModule>* Output)
	{
		if (!Output)
		{
			return false;
		}

		HMODULE Modules[1024];
		HANDLE Process = GetCurrentProcess();
		DWORD BytesNeeded;

		if (EnumProcessModules(Process, Modules, sizeof(Modules), &BytesNeeded))
		{
			for (unsigned int Iter = 0; Iter < (BytesNeeded / sizeof(HMODULE)); ++Iter)
			{
				ProcessModule Module;

				char ModuleName[MAX_PATH];

				if (GetModuleFileNameA(Modules[Iter], ModuleName, sizeof(ModuleName)))
				{
					Module.Name = ModuleName;
				}

				MODULEINFO Info;

				if (GetModuleInformation(GetCurrentProcess(), Modules[Iter], &Info, sizeof(Info)))
				{
					DWORD64* AddressDWORD64 = static_cast<DWORD64*>(Info.lpBaseOfDll);

					char AddressBuffer[64];
					snprintf(AddressBuffer, sizeof(AddressBuffer), "0x%016llX", static_cast<unsigned long long>(*AddressDWORD64));

					Module.BaseAddress = AddressBuffer;
				}

				WIN32_FILE_ATTRIBUTE_DATA FileInfo;

				if (GetFileAttributesExA(ModuleName, GetFileExInfoStandard, &FileInfo))
				{
					LARGE_INTEGER FileSizeBytes;
					FileSizeBytes.HighPart = FileInfo.nFileSizeHigh;
					FileSizeBytes.LowPart = FileInfo.nFileSizeLow;
					
					Module.FileSize = FileSizeBytes.QuadPart;
				}

				Output->push_back(Module);
			}
		}
		
		else
		{
			return false;
		}

		return true;
	}
}  // namespace Red