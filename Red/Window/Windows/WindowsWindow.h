/*
	Copyright (c) 2018 Andrew Depke
*/
#pragma once

#include "../WindowBase.h"

#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace Red
{
	class WindowsWindow : public IWindow
	{
	protected:
		HWND Handle;

	public:
		WindowsWindow() {}
		virtual ~WindowsWindow() {}

		virtual bool Initialize(const WindowDescription& InDescription) override;
		virtual bool Destroy() override;

		virtual void Enable() override;
		virtual void Disable() override;

		virtual void Minimize() override;
		virtual void Maximize() override;
		virtual void Show() override;
		virtual void Hide() override;

		virtual bool SetLocation(const Vector2& NewLocation) override;
		virtual bool SetSize(const Vector2& NewSize) override;
		virtual bool SetFullscreen(bool Fullscreen) override;

		virtual Vector2 GetLocation() const override;
		virtual Vector2 GetSize() const override;
		virtual bool GetFullscreen() const override;
	};

	typedef WindowsWindow Window;

	bool WindowsWindow::Initialize(const WindowDescription& InDescription)
	{
		Description = InDescription;

		wchar_t* AppTitle = new wchar_t[Description.Title.length() + 1];
		wcsncpy_s(AppTitle, Description.Title.length() + 1, Description.Title.c_str(), Description.Title.length() + 1);

		WNDCLASSEX WindowClass;
		ZeroMemory(&WindowClass, sizeof(WindowClass));
		WindowClass.cbSize = sizeof(WindowClass);
		WindowClass.hInstance = Description.Instance;
		WindowClass.style = CS_HREDRAW | CS_VREDRAW | Description.Style;
		WindowClass.lpfnWndProc = (WNDPROC)Description.MessageProcessor;
		WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		WindowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
		WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		WindowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		WindowClass.lpszClassName = AppTitle;

		if (!RegisterClassEx(&WindowClass))
		{
			if (AppTitle)
			{
				delete[] AppTitle;

				AppTitle = 0;
			}

			return false;
		}

		Handle = CreateWindowEx(
			Description.StyleEx,
			AppTitle,
			AppTitle,
			Description.Style,
			(int)Description.Location.X,
			(int)Description.Location.Y,
			(int)Description.Size.X,
			(int)Description.Size.Y,
			NULL,
			NULL,
			Description.Instance,
			NULL);
		if (!Handle)
		{
			if (AppTitle)
			{
				delete[] AppTitle;

				AppTitle = 0;
			}

			return false;
		}

		CurrentState.Location = Description.Location;
		CurrentState.Size = Description.Size;
		CurrentState.Fullscreen = false;

		if (AppTitle)
		{
			delete[] AppTitle;

			AppTitle = 0;
		}

		if (Description.AutoShow)
		{
			Show();
		}

		if (Description.Fullscreen)
		{
			SetFullscreen(true);
		}

		return true;
	}

	bool WindowsWindow::Destroy()
	{
		return !!DestroyWindow(Handle);
	}

	void WindowsWindow::Enable()
	{
		EnableWindow(Handle, true);
	}

	void WindowsWindow::Disable()
	{
		EnableWindow(Handle, false);
	}

	void WindowsWindow::Minimize()
	{
		ShowWindow(Handle, SW_MINIMIZE);
	}

	void WindowsWindow::Maximize()
	{
		ShowWindow(Handle, SW_MAXIMIZE);
	}

	void WindowsWindow::Show()
	{
		ShowWindow(Handle, SW_SHOW);
	}

	void WindowsWindow::Hide()
	{
		ShowWindow(Handle, SW_HIDE);
	}

	bool WindowsWindow::SetLocation(const Vector2& NewLocation)
	{
		if (SetWindowPos(Handle, HWND_TOP, (int)NewLocation.X, (int)NewLocation.Y, (int)CurrentState.Size.X, (int)CurrentState.Size.Y, NULL))
		{
			CurrentState.Location = NewLocation;

			return true;
		}

		return false;
	}

	bool WindowsWindow::SetSize(const Vector2& NewSize)
	{
		if (SetWindowPos(Handle, HWND_TOP, (int)CurrentState.Location.X, (int)CurrentState.Location.Y, (int)NewSize.X, (int)NewSize.Y, NULL))
		{
			CurrentState.Size = NewSize;

			return true;
		}

		return false;
	}

	bool WindowsWindow::SetFullscreen(bool Fullscreen)
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

				CurrentState.Fullscreen = true;

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

	Red::Vector2 WindowsWindow::GetLocation() const
	{
		return CurrentState.Location;
	}

	Red::Vector2 WindowsWindow::GetSize() const
	{
		return CurrentState.Size;
	}

	bool WindowsWindow::GetFullscreen() const
	{
		return CurrentState.Fullscreen;
	}

}  // namespace Red