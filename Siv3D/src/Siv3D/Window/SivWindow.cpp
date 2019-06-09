//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Window.hpp>
# include <Siv3D/Monitor.hpp>
# include <Siv3DEngine.hpp>
# include "IWindow.hpp"

namespace s3d
{
	namespace Window
	{
		void SetTitle(const String& title)
		{
			Siv3DEngine::Get<ISiv3DWindow>()->setWindowTitle(title);
		}

		const String& GetTitle()
		{
			return Siv3DEngine::Get<ISiv3DWindow>()->getWindowTitle();
		}

		WindowState GetState()
		{
			return Siv3DEngine::Get<ISiv3DWindow>()->getWindowState();
		}

		void SetStyle(const WindowStyle style)
		{
			Siv3DEngine::Get<ISiv3DWindow>()->setStyle(style);
		}

		WindowStyle GetStyle()
		{
			return GetState().style;
		}

		Size ClientSize()
		{
			return GetState().clientSize;
		}

		Point ClientCenter()
		{
			return GetState().clientSize / 2;
		}

		int32 ClientWidth()
		{
			return GetState().clientSize.x;
		}

		int32 ClientHeight()
		{
			return GetState().clientSize.y;
		}

		void SetPos(const Point& pos)
		{
			Siv3DEngine::Get<ISiv3DWindow>()->setPos(pos);
		}

		void SetPos(int32 x, int32 y)
		{
			SetPos(Point(x, y));
		}

		void Centering()
		{
			const auto monitors = System::EnumerateActiveMonitors();

			if (!monitors)
			{
				return;
			}

			const Rect workArea = monitors[System::GetCurrentMonitorIndex()].workArea;
			const Rect windowBounds = Siv3DEngine::Get<ISiv3DWindow>()->getWindowBounds();

			Point pos = workArea.pos + (workArea.size - windowBounds.size) / 2;

			if (pos.y < 0)
			{
				pos.y = 0;
			}

			SetPos(pos);
		}

		bool Resize(const Size& size, const WindowResizeOption option, const bool centering)
		{
			return Siv3DEngine::Get<ISiv3DWindow>()->resizeClient(size, option, centering);
		}

		bool Resize(const int32 width, const int32 height, const WindowResizeOption option, const bool centering)
		{
			return Resize(Size(width, height), option, centering);
		}

		void Maximize()
		{
			Siv3DEngine::Get<ISiv3DWindow>()->maximize();
		}

		void Restore()
		{
			Siv3DEngine::Get<ISiv3DWindow>()->restore();
		}

		void Minimize()
		{
			Siv3DEngine::Get<ISiv3DWindow>()->minimize();
		}

		bool SetFullscreen(const bool fullscreen, const Optional<Size>& fullscreenResolution, const WindowResizeOption option)
		{
			return Siv3DEngine::Get<ISiv3DWindow>()->setFullscreen(fullscreen, fullscreenResolution, option);
		}
	}

# if defined(SIV3D_TARGET_WINDOWS)

	namespace Platform::Windows::Window
	{
		void* GetHWND()
		{
			return Siv3DEngine::Get<ISiv3DWindow>()->getHandle();
		}

		bool ChangeDisplayResolution(const Size& size)
		{
			return Siv3DEngine::Get<ISiv3DWindow>()->changeDisplayResolution(size);
		}
	}

# endif
}
