#pragma once

#include "../Core/Definitions.h"

#include <string>

// Cross Platform System Details

namespace Red
{
	struct Hardware
	{
	private:
		Hardware();

	public:
		static std::string GetOSName();
		static byte GetSystemArchitecture();
		static std::string GetCPUVendor();
		static std::string GetCPUBrand();
		static uint16 GetCPUModel();
		static unsigned int GetCPUCoreCount();
		// Returns Speed in Megahertz
		static uint32 GetCPUClockSpeed();
		// Returns Physical Memory Size in Megabytes
		static uint64 GetSystemPhysicalMemory();
		// Returns Virtual Memory Size in Megabytes
		static uint64 GetSystemVirtualMemory();
		// Returns Usable Physical Memory Size in Megabytes
		static uint64 GetSystemPhysicalMemoryAvailable();
		// Returns Usable Virtual Memory Size in Megabytes
		static uint64 GetSystemVirtualMemoryAvailable();
		// Returns Disk Space of the Disk Where the Executable is Housed in Megabytes
		static uint64 GetSystemDiskSpace();
		// Returns Usable Disk Space of the Disk Where the Executable is Housed in Megabytes
		static uint64 GetSystemDiskSpaceAvailable();
	};
}  // namespace Red