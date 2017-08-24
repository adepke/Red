#pragma once

#include "../Core/Platform.h"

#if OS_WINDOWS
	#include "Windows/WindowsWindowDescription.h"
#endif

// WindowDescription is a typedef to a platform specific implementation.