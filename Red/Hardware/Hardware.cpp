#include "Hardware.h"

#include "../Core/Platform.h"
#include <thread>

#if OS_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#include <intrin.h>
	#include <Pdh.h>
	#include <direct.h>
#elif OS_MACINTOSH || OS_BSD
	#include <sys/types>
	#include <sys/sysctl>
#elif OS_LINUX
	#include <unistd.h>
	#include <cpuid.h>
#endif

namespace Red
{
	std::string Hardware::GetOSName()
	{
#if OS_WINDOWS
		return "Windows";
#elif OS_MACINTOSH
		return "Macintosh";
#elif OS_LINUX
		return "Linux";
#elif OS_BSD
		return "BSD";
#elif OS_ANDROID
		return "Android";
#elif OS_IOS
		return "iOS";
#endif
		return "Unknown";
	}

	byte Hardware::GetSystemArchitecture()
	{
		return 0;
	}

	std::string Hardware::GetCPUVendor()
	{
		int Data[4] = { 0 };
		char Vendor[13] = { 0 };

#if OS_WINDOWS
		__cpuid(Data, 0);
		// CPU vendor is stored in EBX EDX ECX (ASCII)
		memcpy(Vendor + 0, &Data[1], 4);  // EBX
		memcpy(Vendor + 4, &Data[3], 4);  // ECX
		memcpy(Vendor + 8, &Data[2], 4);  // EDX
#elif OS_LINUX
		if (__get_cpuid(1, &Data[0], &Data[1], &Data[2], &Data[3]) != 0)
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
#else
		return "System Unsupported";
#endif

		Vendor[12] = '\0';

		return Vendor;
	}

	std::string Hardware::GetCPUBrand()
	{
		char Brand[49] = { 0 };

#if OS_WINDOWS
		int Data[4] = { 0 };

		__cpuid(Data, 0x80000002);
		memcpy(Brand + 0, &Data[0], 4);
		memcpy(Brand + 4, &Data[1], 4);
		memcpy(Brand + 8, &Data[2], 4);
		memcpy(Brand + 12, &Data[3], 4);
		__cpuid(Data, 0x80000003);
		memcpy(Brand + 16, &Data[0], 4);
		memcpy(Brand + 20, &Data[1], 4);
		memcpy(Brand + 24, &Data[2], 4);
		memcpy(Brand + 28, &Data[3], 4);
		__cpuid(Data, 0x80000004);
		memcpy(Brand + 32, &Data[0], 4);
		memcpy(Brand + 36, &Data[1], 4);
		memcpy(Brand + 40, &Data[2], 4);
		memcpy(Brand + 44, &Data[3], 4);
#else
		return "System Unsupported";
#endif

		Brand[48] = '\0';

		return Brand;
	}

	uint16 Hardware::GetCPUModel()
	{
#if OS_WINDOWS
		SYSTEM_INFO SystemInfo;
		GetSystemInfo(&SystemInfo);

		return SystemInfo.wProcessorRevision;
#endif

		return 0;
	}

	unsigned int Hardware::GetCPUCoreCount()
	{
		return std::thread::hardware_concurrency();
	}

	uint32 Hardware::GetCPUClockSpeed()
	{
		uint32 Value;

#if OS_WINDOWS
		const uint32 BufferSize = sizeof(DWORD);
		const uint32 Type = REG_DWORD;
		HKEY Key;

		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &Key) != ERROR_SUCCESS)
		{
			return 0;
		}

		RegQueryValueEx(Key, "~MHz", NULL, (LPDWORD)&Type, (LPBYTE)&Value, (LPDWORD)&BufferSize);
#endif

		return Value;
	}

	uint64 Hardware::GetSystemPhysicalMemory()
	{
#if OS_WINDOWS
		MEMORYSTATUSEX Status;
		Status.dwLength = sizeof(Status);
		GlobalMemoryStatusEx(&Status);

		return (Status.ullTotalPhys / 1024 / 1024);
#elif OS_MACINTOSH || OS_BSD
		int Memory[2] = { CTL_HW, HW_MEMSIZE };
		unsigned int NameLength = sizeof(Memory / sizeof(Memory[0]));
		uint64_t Size;
		size_t Length = sizeof(Size);

		return sysctl(Memory, NameLength, &Size, &Length, NULL, 0);
#elif OS_LINUX
		return (sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGE_SIZE));
#endif

		return 0;
	}

	uint64 Hardware::GetSystemVirtualMemory()
	{
#if OS_WINDOWS
		MEMORYSTATUSEX Status;
		Status.dwLength = sizeof(Status);
		GlobalMemoryStatusEx(&Status);

		return (Status.ullTotalVirtual / 1024 / 1024);
#endif

		return 0;
	}

	uint64 Hardware::GetSystemPhysicalMemoryAvailable()
	{
#if OS_WINDOWS
		MEMORYSTATUSEX Status;
		Status.dwLength = sizeof(Status);
		GlobalMemoryStatusEx(&Status);

		return (Status.ullAvailPhys / 1024 / 1024);
#endif

		return 0;
	}

	uint64 Hardware::GetSystemVirtualMemoryAvailable()
	{
#if OS_WINDOWS
		MEMORYSTATUSEX Status;
		Status.dwLength = sizeof(Status);
		GlobalMemoryStatusEx(&Status);

		return (Status.ullAvailVirtual / 1024 / 1024);
#endif

		return 0;
	}

	uint64 Hardware::GetSystemDiskSpace()
	{
#if OS_WINDOWS
		const byte Drive = static_cast<byte>(_getdrive());
		_diskfree_t DiskFree;

		_getdiskfree(Drive, &DiskFree);

		// Casts to a floating point of 0.01 scale to prevent overflow when multiplying. After dividing down to get megabytes, scale back up and return.
		return static_cast<uint64>((((static_cast<float>(DiskFree.total_clusters) * 0.01f) * DiskFree.sectors_per_cluster * DiskFree.bytes_per_sector) / 1024 / 1024) * 100.0f);
#endif

		return 0;
	}

	uint64 Hardware::GetSystemDiskSpaceAvailable()
	{
#if OS_WINDOWS
		const byte Drive = static_cast<byte>(_getdrive());
		_diskfree_t DiskFree;

		_getdiskfree(Drive, &DiskFree);

		// Casts to a floating point of 0.01 scale to prevent overflow when multiplying. After dividing down to get megabytes, scale back up and return.
		return static_cast<uint64>((((static_cast<float>(DiskFree.avail_clusters) * 0.01f) * DiskFree.sectors_per_cluster * DiskFree.bytes_per_sector) / 1024 / 1024) * 100.0f);
#endif
	}
}  // namespace Red