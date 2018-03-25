/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#include "LinuxHardware.h"

#include "../../Core/Platform.h"

#include <cstring>  // std::memcpy()
#include <unistd.h>
#include <cpuid.h>
#include <thread>
#include <sys/vfs.h>

namespace Red
{
	std::string LinuxSystemHardware::GetOSName()
	{
#if OS_LINUX
		return "Linux";
#elif OS_ANDROID
		return "Android";
#elif OS_BSD
		return "BSD";
#else
		return "Unknown";
#endif
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

		return Vendor;
	}

	std::string LinuxSystemHardware::GetCPUBrand()
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

	unsigned long int LinuxSystemHardware::GetDiskSpace()
	{
		char Directory[1024];

		getcwd(Directory, sizeof(Directory));

		struct statfs FileSystemStats = { 0 };

		if (statfs(Directory, &FileSystemStats) == 0)
		{
			return (FileSystemStats.f_blocks * FileSystemStats.f_bsize / 1024);
		}

		return 0;
	}

	unsigned long int LinuxSystemHardware::GetDiskSpaceAvailable()
	{
		char Directory[1024];

		getcwd(Directory, sizeof(Directory));

		struct statfs FileSystemStats = { 0 };

		if (statfs(Directory, &FileSystemStats) == 0)
		{
			return (FileSystemStats.f_bavail * FileSystemStats.f_bsize / 1024);
		}

		return 0;
	}
}  // namespace Red
