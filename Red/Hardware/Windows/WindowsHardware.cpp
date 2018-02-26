#include "WindowsHardware.h"

#include <thread>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <intrin.h>
#include <Pdh.h>
#include <direct.h>

namespace Red
{
	std::string WindowsSystemHardware::GetOSName()
	{
		return "Windows";
	}

	uint8_t WindowsSystemHardware::GetArchitecture()
	{
#ifdef _WIN64
		return 64;
#else
		return 32;
#endif
	}

	std::string WindowsSystemHardware::GetCPUVendor()
	{
		int Data[4] = { 0 };
		char Vendor[13] = { 0 };

		__cpuid(Data, 0);
		// CPU vendor is stored in EBX EDX ECX (ASCII)
		memcpy(Vendor + 0, &Data[1], 4);  // EBX
		memcpy(Vendor + 4, &Data[3], 4);  // ECX
		memcpy(Vendor + 8, &Data[2], 4);  // EDX

		Vendor[12] = '\0';

		return Vendor;
	}

	std::string WindowsSystemHardware::GetCPUBrand()
	{
		int Data[4] = { 0 };
		char Brand[49] = { 0 };

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

		Brand[48] = '\0';

		return Brand;
	}

	uint16_t WindowsSystemHardware::GetCPUModel()
	{
		SYSTEM_INFO SystemInfo;
		GetSystemInfo(&SystemInfo);

		return SystemInfo.wProcessorRevision;
	}

	unsigned int WindowsSystemHardware::GetCPUCoreCount()
	{
		return std::thread::hardware_concurrency();
	}

	int WindowsSystemHardware::GetCPUClockSpeed()
	{
		int Value;

		const int BufferSize = sizeof(DWORD);
		const int Type = REG_DWORD;
		HKEY Key;

		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &Key) != ERROR_SUCCESS)
		{
			return 0;
		}

		RegQueryValueEx(Key, L"~MHz", NULL, (LPDWORD)&Type, (LPBYTE)&Value, (LPDWORD)&BufferSize);

		return Value;
	}

	unsigned long int WindowsSystemHardware::GetPhysicalMemory()
	{
		MEMORYSTATUSEX Status;
		Status.dwLength = sizeof(Status);
		GlobalMemoryStatusEx(&Status);

		return static_cast<unsigned long int>(Status.ullTotalPhys / 1024 / 1024);
	}

	unsigned long int WindowsSystemHardware::GetVirtualMemory()
	{
		MEMORYSTATUSEX Status;
		Status.dwLength = sizeof(Status);
		GlobalMemoryStatusEx(&Status);

		return static_cast<unsigned long int>(Status.ullTotalVirtual / 1024 / 1024);
	}

	unsigned long int WindowsSystemHardware::GetPhysicalMemoryAvailable()
	{
		MEMORYSTATUSEX Status;
		Status.dwLength = sizeof(Status);
		GlobalMemoryStatusEx(&Status);

		return static_cast<unsigned long int>(Status.ullAvailPhys / 1024 / 1024);
	}

	unsigned long int WindowsSystemHardware::GetVirtualMemoryAvailable()
	{
		MEMORYSTATUSEX Status;
		Status.dwLength = sizeof(Status);
		GlobalMemoryStatusEx(&Status);

		return static_cast<unsigned long int>(Status.ullAvailVirtual / 1024 / 1024);
	}

	unsigned long int WindowsSystemHardware::GetDiskSpace()
	{
		const uint8_t Drive = static_cast<uint8_t>(_getdrive());
		_diskfree_t DiskFree;

		_getdiskfree(Drive, &DiskFree);

		// Casts to a floating point of 0.01 scale to prevent overflow when multiplying. After dividing down to get megabytes, scale back up and return.
		return static_cast<unsigned long int>((((static_cast<float>(DiskFree.total_clusters) * 0.01f) * DiskFree.sectors_per_cluster * DiskFree.bytes_per_sector) / 1024 / 1024) * 100.0f);
	}

	unsigned long int WindowsSystemHardware::GetDiskSpaceAvailable()
	{
		const uint8_t Drive = static_cast<uint8_t>(_getdrive());
		_diskfree_t DiskFree;

		_getdiskfree(Drive, &DiskFree);

		// Casts to a floating point of 0.01 scale to prevent overflow when multiplying. After dividing down to get megabytes, scale back up and return.
		return static_cast<unsigned long int>((((static_cast<float>(DiskFree.avail_clusters) * 0.01f) * DiskFree.sectors_per_cluster * DiskFree.bytes_per_sector) / 1024 / 1024) * 100.0f);
	}
}  // namespace Red