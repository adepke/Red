/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include "../Core/Platform.h"

#if OS_WINDOWS
	#include "Windows/WindowsWindow.h"
#endif

// Window is a typedef to a platform specific implementation.