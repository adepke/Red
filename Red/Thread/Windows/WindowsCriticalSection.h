#pragma once

#include <Windows.h>

namespace Red
{
	class WindowsCriticalSection
	{
	private:
		CRITICAL_SECTION Handle;

	public:
		WindowsCriticalSection();
		~WindowsCriticalSection();

		void Lock();
		void Unlock();

	private:
		WindowsCriticalSection(const WindowsCriticalSection& Target);
		WindowsCriticalSection& operator=(const WindowsCriticalSection& Target);
	};

	// Private inheritance to prevent calls to Lock() and Unlock()
	class WindowsRAIICriticalSection : private WindowsCriticalSection
	{
	public:
		WindowsRAIICriticalSection()
		{
			WindowsCriticalSection::Lock();
		}

		~WindowsRAIICriticalSection()
		{
			WindowsCriticalSection::Unlock();
		}
	};

	typedef WindowsCriticalSection CriticalSection;
	typedef WindowsRAIICriticalSection RAIICriticalSection;
}  // namespace Red