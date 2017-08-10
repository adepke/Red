#pragma once

#include <Windows.h>

namespace Red
{
	class WindowsCriticalSection
	{
	private:
		CRITICAL_SECTION CriticalSectionHandle;

	public:
		WindowsCriticalSection();
		~WindowsCriticalSection();

		void Lock();
		void Unlock();
	};

	typedef WindowsCriticalSection CriticalSection;
}  // namespace Red