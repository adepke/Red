/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#include "DarwinProcess.h"

#include <mach-o/dyld.h>
#include <string.h>

namespace Red
{
	bool GetProcessModules(std::vector<ProcessModule>* Output)
	{
		unsigned int ModuleCount = _dyld_image_count();
		if (ModuleCount == 0)
		{
			return false;
		}

		for (unsigned int Iter = 0; Iter < ModuleCount; ++Iter)
		{
			ProcessModule Module;

			Module.Name = _dyld_get_image_name(Iter);
			Module.BaseAddress = "";
			Module.FileSize = 0;

			Output->push_back(Module);
		}

		return true;
	}
}  // namespace Red