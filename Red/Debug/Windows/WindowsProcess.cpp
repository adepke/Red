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
			for (int Iter = 0; Iter < (BytesNeeded / sizeof(HMODULE)); ++Iter)
			{
				char ModuleName[MAX_PATH];

				if (GetModuleFileNameA(Modules[Iter], ModuleName, (sizeof(ModuleName) / sizeof(sizeof(TCHAR)))))
				{
					ProcessModule Module;
					Module.Name = ModuleName;

					Output->push_back(Module);
				}
			}
		}
		
		else
		{
			return false;
		}

		return true;
	}
}  // namespace Red