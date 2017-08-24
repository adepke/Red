#pragma once

#include <cstdint>
#include <string>

namespace Red
{
	struct WindowsSystemHardware
	{
		static std::string GetOSName();
		static uint8_t GetArchitecture();
		static std::string GetCPUVendor();
		static std::string GetCPUBrand();
		static uint16_t GetCPUModel();
		static unsigned int GetCPUCoreCount();
		// Returns Speed in Megahertz
		static int GetCPUClockSpeed();
		// Returns Physical Memory Size in Megabytes
		static unsigned long int GetPhysicalMemory();
		// Returns Virtual Memory Size in Megabytes
		static unsigned long int GetVirtualMemory();
		// Returns Usable Physical Memory Size in Megabytes
		static unsigned long int GetPhysicalMemoryAvailable();
		// Returns Usable Virtual Memory Size in Megabytes
		static unsigned long int GetVirtualMemoryAvailable();
		// Returns Disk Space of the Disk Where the Executable is Housed in Megabytes
		static unsigned long int GetDiskSpace();
		// Returns Usable Disk Space of the Disk Where the Executable is Housed in Megabytes
		static unsigned long int GetDiskSpaceAvailable();
	};

	struct WindowsExternalHardware
	{

	};

	typedef WindowsSystemHardware SystemHardware;
	typedef WindowsExternalHardware ExternalHardware;
}  // namespace Red