/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include <string>

namespace Red
{
	struct DarwinSystemHardware
	{
		static std::string GetOSName();
		static uint8_t GetArchitecture();
		static std::string GetCPUVendor();
		static std::string GetCPUBrand();
		static unsigned int GetCPUCoreCount();
		// Returns Physical Memory Size in Megabytes
		static unsigned long int GetPhysicalMemory();
	};

	struct DarwinExternalHardware
	{

	};

	typedef DarwinSystemHardware SystemHardware;
	typedef DarwinExternalHardware ExternalHardware;
}  // namespace Red