#pragma once

#include "WindowUtils.h"

namespace Red
{
	// Generic Interface to a Window
	class IWindow
	{
	protected:
		WindowDescription Description;
		WindowState CurrentState;
		WindowState CachedState;  // Used primarily for switching between fullscreen and windowed.

	public:
		virtual bool Initialize(const WindowDescription& InDescription) = 0;
		virtual bool Destroy() = 0;

		virtual void Enable() = 0;
		virtual void Disable() = 0;

		virtual void Minimize() = 0;
		virtual void Maximize() = 0;
		virtual void Show() = 0;
		virtual void Hide() = 0;

		virtual bool SetLocation(const Vector2& NewLocation) = 0;
		virtual bool SetSize(const Vector2& NewSize) = 0;
		virtual bool SetFullscreen(bool Fullscreen) = 0;

		virtual Vector2 GetLocation() const = 0;
		virtual Vector2 GetSize() const = 0;
		virtual bool GetFullscreen() const = 0;
	};
}  // namespace Red