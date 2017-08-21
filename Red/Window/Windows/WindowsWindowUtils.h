#pragma once

#include "../../Math/Vector.h"
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace Red
{
	struct WindowsWindowDescription
	{
	public:
		HINSTANCE Instance;
		WNDPROC MessageProcessor;
		std::string Title;
		DWORD Style;
		DWORD StyleEx;
		Vector2 Size;
		Vector2 Location;
		bool Fullscreen;
	};

	struct WindowsWindowState
	{
		DWORD Style;
		DWORD StyleEx;
		Vector2 Location;
		Vector2 Size;
		bool Fullscreen;
	};

	typedef WindowsWindowDescription WindowDescription;
	typedef WindowsWindowState WindowState;
}  // namespace Red