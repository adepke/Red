/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include "../Core/Platform.h"

#if OS_WINDOWS
	#include "Windows/WindowsStackTrace.h"
#elif OS_MACINTOSH
	#include "Linux/LinuxStackTrace.h"
#elif OS_LINUX
	#include "Linux/LinuxStackTrace.h"
#elif OS_BSD
	#include "Linux/LinuxStackTrace.h"
#elif OS_ANDROID
	#include "Linux/LinuxStackTrace.h"
#elif OS_IOS
	#include "Linux/LinuxStackTrace.h"
#endif

// StackTrace is a typedef to the platform specific implementation of a stack tracer.