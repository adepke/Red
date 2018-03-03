/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include "../Core/Platform.h"

#if   OS_WINDOWS
	#include "BSD/BSDSocket.h"
#elif OS_MACINTOSH
	#include "BSD/BSDSocket.h"
#elif OS_LINUX
	#include "BSD/BSDSocket.h"
#elif OS_BSD
	#include "BSD/BSDSocket.h"
#elif OS_ANDROID
	#include "BSD/BSDSocket.h"
#elif OS_IOS
	#include "BSD/BSDSocket.h"
#endif

// Socket is a typedef to a platform specific implementation.