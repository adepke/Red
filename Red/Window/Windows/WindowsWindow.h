#pragma once

#include "../WindowBase.h"

namespace Red
{
	class WindowsWindow : public IWindow
	{
	protected:
		HWND Handle;

	public:
		WindowsWindow();
		virtual ~WindowsWindow();

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
}  // namespace Red