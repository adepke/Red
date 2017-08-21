#include "WindowsWindow.h"

Red::WindowsWindow::WindowsWindow()
{

}

Red::WindowsWindow::~WindowsWindow()
{

}

bool Red::WindowsWindow::Initialize(const WindowDescription& InDescription)
{
	Description = InDescription;

	WNDCLASSEX WindowClass;
	WindowClass.cbSize = sizeof(WindowClass);
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = Description.MessageProcessor;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WindowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WindowClass.lpszMenuName = NULL;
	WindowClass.lpszClassName = Description.Title.c_str();

	if (!RegisterClassEx(&WindowClass))
	{
		return false;
	}

	Handle = CreateWindowEx(
		NULL,
		Description.Title.c_str(),
		"Application",
		Description.Style,
		Description.Location.X,
		Description.Location.Y,
		Description.Size.X,
		Description.Size.Y,
		NULL,
		NULL,
		Description.Instance,
		NULL);
	if (!Handle)
	{
		return false;
	}

	CurrentState.Location = Description.Location;
	CurrentState.Size = Description.Size;
	CurrentState.Fullscreen = Description.Fullscreen;

	return true;
}

bool Red::WindowsWindow::Destroy()
{
	return !!DestroyWindow(Handle);
}

void Red::WindowsWindow::Minimize()
{
	ShowWindow(Handle, SW_MINIMIZE);
}

void Red::WindowsWindow::Maximize()
{
	ShowWindow(Handle, SW_MAXIMIZE);
}

void Red::WindowsWindow::Enable()
{
	EnableWindow(Handle, true);
}

void Red::WindowsWindow::Disable()
{
	EnableWindow(Handle, false);
}

void Red::WindowsWindow::Show()
{
	ShowWindow(Handle, SW_SHOW);
}

void Red::WindowsWindow::Hide()
{
	ShowWindow(Handle, SW_HIDE);
}

bool Red::WindowsWindow::SetLocation(const Vector2& NewLocation)
{
	if (SetWindowPos(Handle, HWND_TOP, (int)NewLocation.X, (int)NewLocation.Y, (int)CurrentState.Size.X, (int)CurrentState.Size.Y, NULL))
	{
		CurrentState.Location = NewLocation;

		return true;
	}

	return false;
}

bool Red::WindowsWindow::SetSize(const Vector2& NewSize)
{
	if (SetWindowPos(Handle, HWND_TOP, (int)CurrentState.Location.X, (int)CurrentState.Location.Y, (int)NewSize.X, (int)NewSize.Y, NULL))
	{
		CurrentState.Size = NewSize;

		return true;
	}

	return false;
}

bool Red::WindowsWindow::SetFullscreen(bool Fullscreen)
{
	if (Fullscreen)
	{
		// If we're already in fullscreen.
		if (CurrentState.Fullscreen)
		{
			return true;
		}

		else
		{
			CachedState = CurrentState;

			// Remove WS_CAPTION, WS_THICKFRAME, WS_EX_DLGMODALFRAME, WS_EX_WINDOWEDGE, WS_EX_CLIENTEDGE, and WS_EX_STATICEDGE flags.
			CurrentState.Style &= ~(WS_CAPTION | WS_THICKFRAME);
			CurrentState.StyleEx &= ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
			SetWindowLong(Handle, GWL_STYLE, CurrentState.Style);
			SetWindowLong(Handle, GWL_EXSTYLE, CurrentState.StyleEx);

			MONITORINFO MonitorInfo;
			MonitorInfo.cbSize = sizeof(MonitorInfo);

			GetMonitorInfo(MonitorFromWindow(Handle, MONITOR_DEFAULTTONEAREST), &MonitorInfo);
			
			CurrentState.Location.X = (float)MonitorInfo.rcMonitor.left;
			CurrentState.Location.Y = (float)MonitorInfo.rcMonitor.top;
			CurrentState.Size.X = (float)MonitorInfo.rcMonitor.right - MonitorInfo.rcMonitor.left;
			CurrentState.Size.Y = (float)MonitorInfo.rcMonitor.top - MonitorInfo.rcMonitor.bottom;

			SetWindowPos(Handle, HWND_TOP, (int)CurrentState.Location.X, (int)CurrentState.Location.Y, (int)CurrentState.Size.X, (int)CurrentState.Size.Y, SWP_FRAMECHANGED);

			SendMessage(Handle, WM_SYSCOMMAND, SC_MAXIMIZE, 0);

			return true;
		}
	}

	else
	{
		if (CurrentState.Fullscreen)
		{
			SetWindowLong(Handle, GWL_STYLE, CachedState.Style);
			SetWindowLong(Handle, GWL_EXSTYLE, CachedState.StyleEx);

			SetWindowPos(Handle, HWND_TOP, (int)CachedState.Location.X, (int)CachedState.Location.Y, (int)CachedState.Size.X, (int)CachedState.Size.Y, SWP_FRAMECHANGED);
			
			CurrentState = CachedState;

			return true;
		}

		// If we're already not in fullscreen.
		else
		{
			return true;
		}
	}

	return false;
}

Red::Vector2 Red::WindowsWindow::GetLocation() const
{
	return CurrentState.Location;
}

Red::Vector2 Red::WindowsWindow::GetSize() const
{
	return CurrentState.Size;
}

bool Red::WindowsWindow::GetFullscreen() const
{
	return CurrentState.Fullscreen;
}