//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Cursor.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/Cursor/ICursor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Cursor
	{
		Point Pos()
		{
			return SIV3D_ENGINE(Cursor)->getState().point.current;
		}

		Vec2 PosF()
		{
			return SIV3D_ENGINE(Cursor)->getState().vec2.current;
		}

		Point PreviousPos()
		{
			return SIV3D_ENGINE(Cursor)->getState().point.previous;
		}

		Vec2 PreviousPosF()
		{
			return SIV3D_ENGINE(Cursor)->getState().vec2.previous;
		}

		Point Delta()
		{
			return SIV3D_ENGINE(Cursor)->getState().point.delta;
		}

		Vec2 DeltaF()
		{
			return SIV3D_ENGINE(Cursor)->getState().vec2.delta;
		}

		Point PosRaw()
		{
			return SIV3D_ENGINE(Cursor)->getState().raw.current;
		}

		Point PreviousPosRaw()
		{
			return SIV3D_ENGINE(Cursor)->getState().raw.previous;
		}

		Point DeltaRaw()
		{
			return SIV3D_ENGINE(Cursor)->getState().raw.delta;
		}

		Point ScreenPos()
		{
			return SIV3D_ENGINE(Cursor)->getState().screen.current;
		}

		Point ScreenPreviousPos()
		{
			return SIV3D_ENGINE(Cursor)->getState().screen.previous;
		}

		Point ScreenDelta()
		{
			return SIV3D_ENGINE(Cursor)->getState().screen.delta;
		}

		void SetPos(const Point pos)
		{
			SIV3D_ENGINE(Cursor)->setPos(pos);
		}

		bool OnClientRect()
		{
			return Rect(Window::GetState().frameBufferSize)
				.intersects(SIV3D_ENGINE(Cursor)->getState().raw.current);
		}

		bool IsClippedToWindow() noexcept
		{
			return SIV3D_ENGINE(Cursor)->isClippedToWindow();
		}

		void ClipToWindow(const bool clip)
		{
			SIV3D_ENGINE(Cursor)->clipToWindow(clip);
		}

		void SetDefaultStyle(const CursorStyle style)
		{
			SIV3D_ENGINE(Cursor)->setDefaultStyle(style);
		}

		void RequestStyle(const CursorStyle style)
		{
			SIV3D_ENGINE(Cursor)->requestStyle(style);
		}

		bool RegisterCustomCursorStyle(const StringView name, const Image& image, const Point hotSpot)
		{
			return SIV3D_ENGINE(Cursor)->registerCursor(name, image, hotSpot);
		}

		void RequestStyle(const StringView name)
		{
			SIV3D_ENGINE(Cursor)->requestStyle(name);
		}
	}
}
