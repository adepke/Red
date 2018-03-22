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
		HMODULE Modules[1024];
		HANDLE Process = GetCurrentProcess();
		DWORD BytesNeeded;

		if (EnumProcessModules(Process, Modules, sizeof(Modules), &BytesNeeded))
		{
			for (int Iter = 0; Iter < (BytesNeeded / sizeof(HMODULE)); ++Iter)
			{
				TCHAR ModuleName[MAX_PATH];

				if (GetModuleFileName(Modules[Iter], ModuleName, (sizeof(ModuleName) / sizeof(sizeof(TCHAR)))))
				{
					int StringSize = WideCharToMultiByte(CP_UTF8, 0, ModuleName, MAX_PATH, NULL, 0, NULL, NULL);

					std::string ModuleNameMB(StringSize, 0);

					WideCharToMultiByte(CP_UTF8, 0, ModuleName, MAX_PATH, &ModuleNameMB[0], StringSize, NULL, NULL);

					ProcessModule Module;
					Module.Name = ModuleNameMB;

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