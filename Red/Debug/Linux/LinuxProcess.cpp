/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#include "LinuxProcess.h"

#include <link.h>
#include <sys/stat.h>

namespace Red
{
	int ProcessModuleCallback(dl_phdr_info* Info, size_t Size, void* Data)
	{
		ProcessModule Module;

		char AddressBuffer[64];
		snprintf(AddressBuffer, sizeof(AddressBuffer), "0x%016llX", static_cast<unsigned long long>(Info->dlpi_addr));

		Module.BaseAddress = AddressBuffer;
		Module.Name = Info->dlpi_name;

		struct stat FileInfo;

		if (stat(Info->dlpi_name, &FileInfo) != -1)
		{
			Module.FileSize = FileInfo.st_size;
		}

		reinterpret_cast<std::vector<ProcessModule>*>(Data)->push_back(Module);
		
		return 0;
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
