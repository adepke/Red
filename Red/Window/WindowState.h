#pragma once

#include "../Core/Platform.h"

#if OS_WINDOWS
	#include "Windows/WindowsWindowState.h"
#endif

// WindowState is a typedef to a platform specific implementation.