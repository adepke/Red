/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#include "LinuxProcess.h"

#include <link.h>

namespace Red
{
	int ProcessModuleCallback(dl_phdr_info* Info, size_t Size, void* Data)
	{
		ProcessModule Module;
		Module.Name = Info->dlpi_name;

		reinterpret_cast<std::vector<ProcessModule>*>(Data)->push_back(Module);
	}

	bool GetProcessModules(std::vector<ProcessModule>* Output)
	{
		if (!Output)
		{
			return false;
		}

		dl_iterate_phdr(&ProcessModuleCallback, reinterpret_cast<void*>(Output));

		return true;
	}
}  // namespace Red
