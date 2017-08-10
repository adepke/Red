#include "WindowsCriticalSection.h"

#include <Windows.h>

namespace Red
{
	WindowsCriticalSection::WindowsCriticalSection()
	{
		InitializeCriticalSection(&Handle);
		SetCriticalSectionSpinCount(&Handle, 2000);
	}

	WindowsCriticalSection::~WindowsCriticalSection()
	{
		DeleteCriticalSection(&Handle);
	}

	void WindowsCriticalSection::Lock()
	{
		EnterCriticalSection(&Handle);
	}

	void WindowsCriticalSection::Unlock()
	{
		LeaveCriticalSection(&Handle);
	}
}  // namespace Red