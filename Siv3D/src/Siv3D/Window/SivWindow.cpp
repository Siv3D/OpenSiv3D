﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Window.hpp>
# include <Siv3D/Utility.hpp>
# include <Siv3D/Error.hpp>
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

		bool ResizeVirtual(const Size size)
		{
			if (!InRange(size.x, 1, 8192) || !InRange(size.y, 1, 8192))
			{
				throw Error(U"Window::ResizeVirtual(): width and height must be in the range [1, 8192]");
			}

			return SIV3D_ENGINE(Window)->resizeByVirtualSize(size);
		}

		bool ResizeActual(const Size size)
		{
			if (!InRange(size.x, 1, 8192) || !InRange(size.y, 1, 8192))
			{
				throw Error(U"Window::ResizeActual(): width and height must be in the range [1, 8192]");
			}

			return SIV3D_ENGINE(Window)->resizeByFrameBufferSize(size);
		}

		void SetMinimumFrameBufferSize(const Size size)
		{
			SIV3D_ENGINE(Window)->setMinimumFrameBufferSize(size);
		}
	}
}
