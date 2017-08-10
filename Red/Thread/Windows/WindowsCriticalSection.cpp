#include "WindowsCriticalSection.h"

#include <Windows.h>

namespace Red
{
	WindowsCriticalSection::WindowsCriticalSection()
	{
		InitializeCriticalSection(&CriticalSectionHandle);
	}

	WindowsCriticalSection::~WindowsCriticalSection()
	{
		DeleteCriticalSection(&CriticalSectionHandle);
	}

	void WindowsCriticalSection::Lock()
	{
		EnterCriticalSection(&CriticalSectionHandle);
	}

	void WindowsCriticalSection::Unlock()
	{
		LeaveCriticalSection(&CriticalSectionHandle);
	}
}  // namespace Red