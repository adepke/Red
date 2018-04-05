/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#include "WindowsHardware.h"

#include <thread>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <intrin.h>
#include <Pdh.h>
#include <direct.h>

#pragma comment(lib, "version.lib")

namespace Red
{
	std::string WindowsSystemHardware::GetOSName()
	{
		return "Windows";
	}

	std::string WindowsSystemHardware::GetOSVersion()
	{
		char KernelPath[MAX_PATH];

		if (!GetSystemDirectoryA(KernelPath, sizeof(KernelPath)))
		{
			// This Might Fail on Windows Phone and Store Apps

			return "";
		}

		strcat_s(KernelPath, "\\kernel32.dll");

		DWORD Handle;
		DWORD Length = GetFileVersionInfoSizeA(KernelPath, &Handle);

		if (Length == 0)
		{
			return "";
		}

		BYTE* KernelVersionInfoBuffer = new BYTE[Length];

		if (GetFileVersionInfoA(KernelPath, NULL, Length, KernelVersionInfoBuffer))
		{
			VS_FIXEDFILEINFO* FileInfo;
			UINT FileInfoSize = 0;

			if (VerQueryValueA(KernelVersionInfoBuffer, "\\", reinterpret_cast<LPVOID*>(&FileInfo), &FileInfoSize))
			{
				if (FileInfoSize)
				{
					char VersionBuffer[128];

					sprintf_s(VersionBuffer, "%u.%u.%u.%u", HIWORD(FileInfo->dwFileVersionMS), LOWORD(FileInfo->dwFileVersionMS), HIWORD(FileInfo->dwFileVersionLS), LOWORD(FileInfo->dwFileVersionLS));

					return std::string(VersionBuffer);
				}
			}
		}

		if (KernelVersionInfoBuffer)
		{
			delete[] KernelVersionInfoBuffer;
		}

		return "";
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
		static std::string CPUVendor;
		if (CPUVendor.length() == 0)
		{
			int Data[4] = { 0 };
			char Vendor[13] = { 0 };

			__cpuid(Data, 0);
			// CPU vendor is stored in EBX EDX ECX (ASCII)
			memcpy(Vendor + 0, &Data[1], 4);  // EBX
			memcpy(Vendor + 4, &Data[3], 4);  // ECX
			memcpy(Vendor + 8, &Data[2], 4);  // EDX

			Vendor[12] = '\0';

			CPUVendor = Vendor;
		}

		return CPUVendor;
	}

	std::string WindowsSystemHardware::GetCPUBrand()
	{
		static std::string CPUBrand;
		if (CPUBrand.length() == 0)
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

			CPUBrand = Brand;
		}

		return CPUBrand;
	}

	uint16_t WindowsSystemHardware::GetCPUModel()
	{
		static uint16_t CPUModel = 0;
		if (CPUModel == 0)
		{
			SYSTEM_INFO SystemInfo;
			GetSystemInfo(&SystemInfo);

			CPUModel = SystemInfo.wProcessorRevision;
		}

		return CPUModel;
	}

	unsigned int WindowsSystemHardware::GetCPUCoreCount()
	{
		static unsigned int CPUCoreCount = 0;
		if (CPUCoreCount == 0)
		{
			DWORD BufferLength = 0;

			GetLogicalProcessorInformation(nullptr, &BufferLength);  // Get the Buffer Size Required

			if (BufferLength == 0)
			{
				return 0;
			}

			const int Count = BufferLength / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);

			if (Count != 0)
			{
				SYSTEM_LOGICAL_PROCESSOR_INFORMATION* ProcessorInfoBuffer = new SYSTEM_LOGICAL_PROCESSOR_INFORMATION[Count];

				if (GetLogicalProcessorInformation(ProcessorInfoBuffer, &BufferLength))
				{
					for (int Iter = 0; Iter < Count; ++Iter)
					{
						if (ProcessorInfoBuffer[Iter].Relationship == RelationProcessorCore)
						{
							++CPUCoreCount;
						}
					}
				}

				delete[] ProcessorInfoBuffer;
			}
		}

		return CPUCoreCount;
	}

	unsigned int WindowsSystemHardware::GetCPULogicalCoreCount()
	{
		static unsigned int CPULogicalCoreCount = 0;
		if (CPULogicalCoreCount == 0)
		{
			CPULogicalCoreCount = std::thread::hardware_concurrency();
		}

		return CPULogicalCoreCount;
	}

	int WindowsSystemHardware::GetCPUClockSpeed()
	{
		static int CPUClockSpeed = 0;
		if (CPUClockSpeed == 0)
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

			CPUClockSpeed = Value;
		}

		return CPUClockSpeed;
	}

	unsigned long int WindowsSystemHardware::GetPhysicalMemory()
	{
		static unsigned long int PhysicalMemory = 0;
		if (PhysicalMemory == 0)
		{
			MEMORYSTATUSEX Status;
			Status.dwLength = sizeof(Status);
			GlobalMemoryStatusEx(&Status);

			PhysicalMemory = static_cast<unsigned long int>(Status.ullTotalPhys / 1024 / 1024);
		}

		return PhysicalMemory;
	}

	unsigned long int WindowsSystemHardware::GetVirtualMemory()
	{
		static unsigned long int VirtualMemory = 0;
		if (VirtualMemory == 0)
		{
			MEMORYSTATUSEX Status;
			Status.dwLength = sizeof(Status);
			GlobalMemoryStatusEx(&Status);

			VirtualMemory = static_cast<unsigned long int>(Status.ullTotalVirtual / 1024 / 1024);
		}

		return VirtualMemory;
	}

	unsigned long int WindowsSystemHardware::GetPhysicalMemoryAvailable()
	{
		static unsigned long int PhysicalMemoryAvailable = 0;
		if (PhysicalMemoryAvailable == 0)
		{
			MEMORYSTATUSEX Status;
			Status.dwLength = sizeof(Status);
			GlobalMemoryStatusEx(&Status);

			PhysicalMemoryAvailable = static_cast<unsigned long int>(Status.ullAvailPhys / 1024 / 1024);
		}

		return PhysicalMemoryAvailable;
	}

	unsigned long int WindowsSystemHardware::GetVirtualMemoryAvailable()
	{
		static unsigned long int VirtualMemoryAvailable = 0;
		if (VirtualMemoryAvailable == 0)
		{
			MEMORYSTATUSEX Status;
			Status.dwLength = sizeof(Status);
			GlobalMemoryStatusEx(&Status);

			VirtualMemoryAvailable = static_cast<unsigned long int>(Status.ullAvailVirtual / 1024 / 1024);
		}

		return VirtualMemoryAvailable;
	}

	unsigned long int WindowsSystemHardware::GetDiskSpace()
	{
		static unsigned long int DiskSpace = 0;
		if (DiskSpace == 0)
		{
			const uint8_t Drive = static_cast<uint8_t>(_getdrive());
			_diskfree_t DiskFree;

			_getdiskfree(Drive, &DiskFree);

			// Casts to a floating point of 0.01 scale to prevent overflow when multiplying. After dividing down to get megabytes, scale back up and return.
			DiskSpace = static_cast<unsigned long int>((((static_cast<float>(DiskFree.total_clusters) * 0.01f) * DiskFree.sectors_per_cluster * DiskFree.bytes_per_sector) / 1024 / 1024) * 100.0f);
		}

		return DiskSpace;
	}

	unsigned long int WindowsSystemHardware::GetDiskSpaceAvailable()
	{
		static unsigned long int DiskSpaceAvailable = 0;
		if (DiskSpaceAvailable == 0)
		{
			const uint8_t Drive = static_cast<uint8_t>(_getdrive());
			_diskfree_t DiskFree;

			_getdiskfree(Drive, &DiskFree);

			// Casts to a floating point of 0.01 scale to prevent overflow when multiplying. After dividing down to get megabytes, scale back up and return.
			DiskSpaceAvailable = static_cast<unsigned long int>((((static_cast<float>(DiskFree.avail_clusters) * 0.01f) * DiskFree.sectors_per_cluster * DiskFree.bytes_per_sector) / 1024 / 1024) * 100.0f);
		}

		return DiskSpaceAvailable;
	}
}  // namespace Red