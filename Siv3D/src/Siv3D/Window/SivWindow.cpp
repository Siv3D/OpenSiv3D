//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Window.hpp>
# include <Siv3D/Utility.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/Monitor.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Window
	{
		void SetTitle(const String& title)
		{
			SIV3D_ENGINE(Window)->setWindowTitle(title);
		}

		const String& GetTitle() noexcept
		{
			return SIV3D_ENGINE(Window)->getWindowTitle();
		}

		const WindowState& GetState() noexcept
		{
			return SIV3D_ENGINE(Window)->getState();
		}

		void SetStyle(const WindowStyle style)
		{
			SIV3D_ENGINE(Window)->setStyle(style);
		}

		void SetPos(const Point pos)
		{
			SIV3D_ENGINE(Window)->setPos(pos);
		}

		void Centering()
		{
			try
			{
				const Monitor currentMonitor = System::GetCurrentMonitor();
				const Rect workArea = System::GetCurrentMonitor().workArea;
				const Rect windowBounds = SIV3D_ENGINE(Window)->getState().bounds;
				const Point pos = (workArea.pos + (workArea.size - windowBounds.size) / 2);

				SetPos(pos);
			}
			catch (const Error&) {}
		}

		void Maximize()
		{
			SIV3D_ENGINE(Window)->maximize();
		}

		void Restore()
		{
			SIV3D_ENGINE(Window)->restore();
		}

		void Minimize()
		{
			SIV3D_ENGINE(Window)->minimize();
		}

		bool ResizeVirtual(const Size size, const s3d::Centering centering)
		{
			if ((not InRange(size.x, 1, 8192))
				|| (not InRange(size.y, 1, 8192)))
			{
				throw Error(U"Window::ResizeVirtual(): width and height must be in the range [1, 8192]");
			}

			if (not SIV3D_ENGINE(Window)->resizeByVirtualSize(size))
			{
				return false;
			}

			if (const auto resizeMode = Scene::GetResizeMode();
				resizeMode == ResizeMode::Actual)
			{
				Scene::Resize(SIV3D_ENGINE(Window)->getState().frameBufferSize);
			}
			else if (resizeMode == ResizeMode::Virtual)
			{
				Scene::Resize(size);
			}

			if (centering)
			{
				Centering();
			}

			return true;
		}

		bool ResizeActual(const Size size, const s3d::Centering centering)
		{
			if ((not InRange(size.x, 1, 8192))
				|| (not InRange(size.y, 1, 8192)))
			{
				throw Error(U"Window::ResizeActual(): width and height must be in the range [1, 8192]");
			}

			if (not SIV3D_ENGINE(Window)->resizeByFrameBufferSize(size))
			{
				return false;
			}

			if (const auto resizeMode = Scene::GetResizeMode();
				resizeMode == ResizeMode::Actual)
			{
				Scene::Resize(SIV3D_ENGINE(Window)->getState().frameBufferSize);
			}
			else if (resizeMode == ResizeMode::Virtual)
			{
				Scene::Resize(size);
			}

			if (centering)
			{
				Centering();
			}

			return true;
		}

		void SetMinimumFrameBufferSize(const Size size)
		{
			SIV3D_ENGINE(Window)->setMinimumFrameBufferSize(size);
		}

		void SetFullscreen(const bool fullscreen, const size_t monitorIndex)
		{
			SIV3D_ENGINE(Window)->setFullscreen(fullscreen, monitorIndex);
		}
	}
}
