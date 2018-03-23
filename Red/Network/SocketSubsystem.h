/*
	Copyright (c) 2017-2018 Andrew Depke
*/
#pragma once

#include "../Core/Platform.h"

#if   OS_WINDOWS
	#include "BSD/BSDSocketSubsystem.h"
#elif OS_MACINTOSH
	#include "BSD/BSDSocketSubsystem.h"
#elif OS_LINUX
	#include "BSD/BSDSocketSubsystem.h"
#elif OS_BSD
	#include "BSD/BSDSocketSubsystem.h"
#elif OS_ANDROID
	#include "BSD/BSDSocketSubsystem.h"
#elif OS_IOS
	#include "BSD/BSDSocketSubsystem.h"
#endif

// SocketSubsystem is a typedef to a platform specific implementation.