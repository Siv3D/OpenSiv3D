//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../Siv3DEngine.hpp"
# include "ICursor.hpp"
# include "../Window/IWindow.hpp"
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Intersection.hpp>
# include <Siv3D/Window.hpp>

namespace s3d
{
	namespace Cursor
	{
		Point Pos()
		{
			return Siv3DEngine::GetCursor()->clientTransformed().current;
		}

		Point PreviousPos()
		{
			return Siv3DEngine::GetCursor()->clientTransformed().previous;
		}

		Point Delta()
		{
			return Siv3DEngine::GetCursor()->clientTransformed().delta;
		}

		Vec2 PosF()
		{
			return Siv3DEngine::GetCursor()->clientTransformedF().current;
		}

		Vec2 PreviousPosF()
		{
			return Siv3DEngine::GetCursor()->clientTransformedF().previous;
		}

		Vec2 DeltaF()
		{
			return Siv3DEngine::GetCursor()->clientTransformedF().delta;
		}

		Point PosRaw()
		{
			return Siv3DEngine::GetCursor()->clientRaw().current;
		}

		Point PreviousPosRaw()
		{
			return Siv3DEngine::GetCursor()->clientRaw().previous;
		}

		Point DeltaRaw()
		{
			return Siv3DEngine::GetCursor()->clientRaw().delta;
		}

		Point ScreenPos()
		{
			return Siv3DEngine::GetCursor()->screen().current;
		}

		Point PreviousScreenPos()
		{
			return Siv3DEngine::GetCursor()->screen().previous;
		}

		Point ScreenDelta()
		{
			return Siv3DEngine::GetCursor()->screen().delta;
		}

		void SetPos(const int32 x, const int32 y)
		{
			Siv3DEngine::GetCursor()->setPos(x, y);
		}

		void SetPos(const Point& pos)
		{
			SetPos(pos.x, pos.y);
		}

		bool OnClientRect()
		{
			return Geometry2D::Intersect(Siv3DEngine::GetCursor()->clientRaw().current,
				Rect(Siv3DEngine::GetWindow()->getState().clientSize));
		}

		void SetTransformLocal(const Mat3x2& matrix) 
		{
			Siv3DEngine::GetCursor()->setTransformLocal(matrix);
		}

		void SetTransformCamera(const Mat3x2& matrix)
		{
			Siv3DEngine::GetCursor()->setTransformCamera(matrix);
		}

		void SetTransformScreen(const Mat3x2& matrix)
		{
			Siv3DEngine::GetCursor()->setTransformScreen(matrix);
		}

		const Mat3x2& GetTransformLocal()
		{
			return Siv3DEngine::GetCursor()->getTransformLocal();
		}

		const Mat3x2& GetTransformCamera()
		{
			return Siv3DEngine::GetCursor()->getTransformCamera();
		}

		const Mat3x2& GetTransformScreen()
		{
			return Siv3DEngine::GetCursor()->getTransformScreen();
		}

		void ClipClientRect(bool clip)
		{
			Siv3DEngine::GetCursor()->clipClientRect(clip);
		}

		void RequestStyle(const CursorStyle style)
		{
			Siv3DEngine::GetCursor()->requestStyle(style);
		}

		void SetDefaultStyle(const CursorStyle style)
		{
			Siv3DEngine::GetCursor()->setDefaultStyle(style);
		}

		CursorStyle GetRequestedStyle()
		{
			return Siv3DEngine::GetCursor()->getRequestedStyle();
		}

		CursorStyle GetDefaultStyle()
		{
			return Siv3DEngine::GetCursor()->getDefaultStyle();
		}
	}

	namespace win::Cursor
	{
		void ClipRect(const Optional<Rect>& rect)
		{
			Siv3DEngine::GetCursor()->clip(rect);
		}
	}
}
