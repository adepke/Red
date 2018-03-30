/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#include "DarwinHardware.h"

#include "../../Core/Platform.h"

#include <cstring>  // std::memcpy()
#include <unistd.h>
#include <cpuid.h>
#include <thread>

namespace Red
{
	std::string DarwinSystemHardware::GetOSName()
	{
#if OS_MACINTOSH
		return "Macintosh";
#elif OS_IOS
		return "iOS";
#else
		return "Unknown";
#endif
	}

	uint8_t DarwinSystemHardware::GetArchitecture()
	{
#if defined(__x86_64__) || defined(__ppc64__)
		return 64;
#else
		return 32;
#endif
	}

	std::string DarwinSystemHardware::GetCPUVendor()
	{
		static std::string CPUVendor = NULL;
		if (CPUVendor.length() == 0)
		{
			unsigned int Data[4] = { 0 };
			char Vendor[13] = { 0 };

			if (__get_cpuid(0, &Data[0], &Data[1], &Data[2], &Data[3]) != 0)
			{
				// CPU vendor is stored in EBX EDX ECX (ASCII)
				std::memcpy(Vendor + 0, &Data[1], 4);  // EBX
				std::memcpy(Vendor + 4, &Data[3], 4);  // ECX
				std::memcpy(Vendor + 8, &Data[2], 4);  // EDX
			}

			else
			{
				return "Error";
			}

			Vendor[12] = '\0';

			CPUVendor = Vendor;
		}

		return CPUVendor;
	}

	std::string DarwinSystemHardware::GetCPUBrand()
	{
		static std::string CPUBrand = NULL;
		if (CPUBrand.length() == 0)
		{
			unsigned int Data[4] = { 0 };
			char Brand[49] = { 0 };

			if (__get_cpuid(0x80000002, &Data[0], &Data[1], &Data[2], &Data[3]) != 0)
			{
				std::memcpy(Brand + 0, &Data[0], 4);
				std::memcpy(Brand + 4, &Data[1], 4);
				std::memcpy(Brand + 8, &Data[2], 4);
				std::memcpy(Brand + 12, &Data[3], 4);
			}

			else
			{
				return "Error";
			}

			if (__get_cpuid(0x80000003, &Data[0], &Data[1], &Data[2], &Data[3]) != 0)
			{
				std::memcpy(Brand + 16, &Data[0], 4);
				std::memcpy(Brand + 20, &Data[1], 4);
				std::memcpy(Brand + 24, &Data[2], 4);
				std::memcpy(Brand + 28, &Data[3], 4);
			}

			else
			{
				return "Error";
			}

			if (__get_cpuid(0x80000004, &Data[0], &Data[1], &Data[2], &Data[3]) != 0)
			{
				std::memcpy(Brand + 32, &Data[0], 4);
				std::memcpy(Brand + 36, &Data[1], 4);
				std::memcpy(Brand + 40, &Data[2], 4);
				std::memcpy(Brand + 44, &Data[3], 4);
			}

			else
			{
				return "Error";
			}

			Brand[48] = '\0';

			CPUBrand = Brand;
		}

		return CPUBrand;
	}

	unsigned int DarwinSystemHardware::GetCPUCoreCount()
	{
		static unsigned int CPUCoreCount = NULL;
		if (CPUCoreCount == 0)
		{
			CPUCoreCount = std::thread::hardware_concurrency();
		}

		return CPUCoreCount;
	}

	unsigned long int DarwinSystemHardware::GetPhysicalMemory()
	{
		static unsigned long int PhysicalMemory = NULL;
		if (PhysicalMemory == 0)
		{
			PhysicalMemory = (sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGE_SIZE));
		}

		return PhysicalMemory;
	}
}  // namespace Red