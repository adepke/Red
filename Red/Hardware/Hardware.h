/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include "../Core/Platform.h"

#if OS_WINDOWS
	#include "Windows/WindowsHardware.h"
#elif OS_MACINTOSH
	#include "Darwin/DarwinHardware.h"
#elif OS_LINUX
	#include "Linux/LinuxHardware.h"
#elif OS_BSD
	#include "Linux/LinuxHardware.h"
#elif OS_ANDROID
	#include "Linux/LinuxHardware.h"
#elif OS_IOS
	#include "Darwin/DarwinHardware.h"
#endif

// SystemHardware is a typedef to a platform specific implementation.
// ExternalHardware is a typedef to a platform specific implementation.