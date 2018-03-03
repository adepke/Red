/*
	Copyright (c) 2018 Andrew Depke
*/
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

	bool WindowsCriticalSection::TryLock()
	{
		return TryEnterCriticalSection(&Handle);
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