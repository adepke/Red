#include "LinuxHardware.h"

#include <unistd.h>
#include <cpuid.h>
#include <thread>

namespace Red
{
	std::string LinuxSystemHardware::GetOSName()
	{
		return "Linux";
	}

	uint8_t LinuxSystemHardware::GetArchitecture()
	{
#if defined(__x86_64__) || defined(__ppc64__)
		return 64;
#else
		return 32;
#endif
	}

	std::string LinuxSystemHardware::GetCPUVendor()
	{
		int Data[4] = { 0 };
		char Vendor[13] = { 0 };

		if (__get_cpuid(0, &Data[0], &Data[1], &Data[2], &Data[3]) != 0)
		{
			// CPU vendor is stored in EBX EDX ECX (ASCII)
			memcpy(Vendor + 0, &Data[1], 4);  // EBX
			memcpy(Vendor + 4, &Data[3], 4);  // ECX
			memcpy(Vendor + 8, &Data[2], 4);  // EDX
		}

		else
		{
			return "Error";
		}

		Vendor[12] = '\0';

		return Vendor;
	}

	std::string LinuxSystemHardware::GetCPUBrand()
	{
		int Data[4] = { 0 };
		char Brand[49] = { 0 };

		if (__get_cpuid(0x80000002, &Data[0], &Data[1], &Data[2], &Data[3]) != 0)
		{
			memcpy(Brand + 0, &Data[0], 4);
			memcpy(Brand + 4, &Data[1], 4);
			memcpy(Brand + 8, &Data[2], 4);
			memcpy(Brand + 12, &Data[3], 4);
		}

		else
		{
			return "Error";
		}

		if (__get_cpuid(0x80000003, &Data[0], &Data[1], &Data[2], &Data[3]) != 0)
		{
			memcpy(Brand + 16, &Data[0], 4);
			memcpy(Brand + 20, &Data[1], 4);
			memcpy(Brand + 24, &Data[2], 4);
			memcpy(Brand + 28, &Data[3], 4);
		}

		else
		{
			return "Error";
		}

		if (__get_cpuid(0x80000004, &Data[0], &Data[1], &Data[2], &Data[3]) != 0)
		{
			memcpy(Brand + 32, &Data[0], 4);
			memcpy(Brand + 36, &Data[1], 4);
			memcpy(Brand + 40, &Data[2], 4);
			memcpy(Brand + 44, &Data[3], 4);
		}

		else
		{
			return "Error";
		}

		Brand[48] = '\0';

		return Brand;
	}

	unsigned int LinuxSystemHardware::GetCPUCoreCount()
	{
		return std::thread::hardware_concurrency();
	}

	unsigned long int LinuxSystemHardware::GetPhysicalMemory()
	{
		return (sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGE_SIZE));
	}
}  // namespace Red