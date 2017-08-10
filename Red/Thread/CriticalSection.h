#pragma once

#include "../Core/Platform.h"

#if OS_WINDOWS
#include "Windows\WindowsCriticalSection.h"
#endif

// CriticalSection is a typedef to the platform specific implementation of a critical section.