#pragma once

#include "../../Math/Vector.h"
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace Red
{
	struct WindowsWindowState
	{
	public:
		DWORD Style;
		DWORD StyleEx;
		Vector2 Location;
		Vector2 Size;
		bool Fullscreen;
	};

	typedef WindowsWindowState WindowState;
}  // namespace Red