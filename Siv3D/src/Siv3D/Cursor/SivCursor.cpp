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
# include <Siv3D/Cursor.hpp>
# include <Siv3DEngine.hpp>
# include "ICursor.hpp"

namespace s3d
{
	namespace Cursor
	{
		Point Pos()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->clientTransformed().current;
		}

		Point PreviousPos()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->clientTransformed().previous;
		}

		Point Delta()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->clientTransformed().delta;
		}

		Vec2 PosF()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->clientTransformedF().current;
		}

		Vec2 PreviousPosF()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->clientTransformedF().previous;
		}

		Vec2 DeltaF()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->clientTransformedF().delta;
		}

		Point PosRaw()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->clientRaw().current;
		}

		Point PreviousPosRaw()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->clientRaw().previous;
		}

		Point DeltaRaw()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->clientRaw().delta;
		}

		Point ScreenPos()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->screen().current;
		}

		Point PreviousScreenPos()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->screen().previous;
		}

		Point ScreenDelta()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->screen().delta;
		}

		Array<std::pair<Point, uint64>> GetBuffer()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->getBufferTransformed();
		}

		void SetPos(const int32 x, const int32 y)
		{
			SetPos(Point(x, y));
		}

		void SetPos(const Point& pos)
		{
			Siv3DEngine::Get<ISiv3DCursor>()->setPos(pos);
		}

		bool OnClientRect()
		{
			return Geometry2D::Intersect(
				Siv3DEngine::Get<ISiv3DCursor>()->clientRaw().current,
				Rect(Window::GetState().clientSize));
		}

		void SetLocalTransform(const Mat3x2& matrix)
		{
			Siv3DEngine::Get<ISiv3DCursor>()->setLocalTransform(matrix);
		}

		void SetCameraTransform(const Mat3x2& matrix)
		{
			Siv3DEngine::Get<ISiv3DCursor>()->setCameraTransform(matrix);
		}

		const Mat3x2& GetLocalTransform()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->getLocalTransform();
		}

		const Mat3x2& GetCameraTransform()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->getCameraTransform();
		}

		void ClipToWindow(bool clip)
		{
			Siv3DEngine::Get<ISiv3DCursor>()->clipToWindow(clip);
		}

		void RequestStyle(const CursorStyle style)
		{
			Siv3DEngine::Get<ISiv3DCursor>()->requestStyle(style);
		}

		void SetDefaultStyle(const CursorStyle style)
		{
			Siv3DEngine::Get<ISiv3DCursor>()->setDefaultStyle(style);
		}

		CursorStyle GetRequestedStyle()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->getRequestedStyle();
		}

		CursorStyle GetDefaultStyle()
		{
			return Siv3DEngine::Get<ISiv3DCursor>()->getDefaultStyle();
		}
	}
}
