//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Cursor.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Cursor/ICursor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Cursor
	{
		Point Pos() noexcept
		{
			return SIV3D_ENGINE(Cursor)->getState().point.current;
		}

		Vec2 PosF() noexcept
		{
			return SIV3D_ENGINE(Cursor)->getState().vec2.current;
		}

		Point PreviousPos() noexcept
		{
			return SIV3D_ENGINE(Cursor)->getState().point.previous;
		}

		Vec2 PreviousPosF() noexcept
		{
			return SIV3D_ENGINE(Cursor)->getState().vec2.previous;
		}

		Point Delta() noexcept
		{
			return SIV3D_ENGINE(Cursor)->getState().point.delta;
		}

		Vec2 DeltaF() noexcept
		{
			return SIV3D_ENGINE(Cursor)->getState().vec2.delta;
		}

		Point PosRaw() noexcept
		{
			return SIV3D_ENGINE(Cursor)->getState().raw.current;
		}

		Point PreviousPosRaw() noexcept
		{
			return SIV3D_ENGINE(Cursor)->getState().raw.previous;
		}

		Point DeltaRaw() noexcept
		{
			return SIV3D_ENGINE(Cursor)->getState().raw.delta;
		}

		Point ScreenPos() noexcept
		{
			return SIV3D_ENGINE(Cursor)->getState().screen.current;
		}

		Point ScreenPreviousPos() noexcept
		{
			return SIV3D_ENGINE(Cursor)->getState().screen.previous;
		}

		Point ScreenDelta() noexcept
		{
			return SIV3D_ENGINE(Cursor)->getState().screen.delta;
		}

		void SetPos(const int32 x, const int32 y)
		{
			SetPos(Point{ x, y });
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

		const Mat3x2& GetLocalTransform() noexcept
		{
			return SIV3D_ENGINE(Cursor)->getLocalTransform();
		}

		const Mat3x2& GetCameraTransform() noexcept
		{
			return SIV3D_ENGINE(Cursor)->getCameraTransform();
		}

		void SetCapture(const bool captured) noexcept
		{
			SIV3D_ENGINE(Cursor)->setCapture(captured);
		}

		bool IsCaptured() noexcept
		{
			return SIV3D_ENGINE(Cursor)->isCaptured();
		}

		namespace Internal
		{
			void SetLocalTransform(const Mat3x2& matrix)
			{
				SIV3D_ENGINE(Cursor)->setLocalTransform(matrix);
			}

			void SetCameraTransform(const Mat3x2& matrix)
			{
				SIV3D_ENGINE(Cursor)->setCameraTransform(matrix);
			}
		}
	}
}
