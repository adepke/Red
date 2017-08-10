#pragma once

#include "../Core/Platform.h"

#if OS_WINDOWS
	#include "Windows\WindowsCriticalSection.h"
#elif OS_MACINTOSH
	#include "POSIX\POSIXCriticalSection.h"
#elif OS_LINUX
	#include "POSIX\POSIXCriticalSection.h"
#elif OS_BSD
	#include "POSIX\POSIXCriticalSection.h"
#elif OS_ANDROID
	#include "POSIX\POSIXCriticalSection.h"
#elif OS_IOS
	#include "POSIX\POSIXCriticalSection.h"
#endif

// CriticalSection is a typedef to the platform specific implementation of a critical section.
// RAIICriticalSection is a typedef to the platform specific implementation of a RAII-based critical section.