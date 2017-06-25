//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
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

		bool OnClientRect()
		{
			return Geometry2D::Intersect(Siv3DEngine::GetCursor()->clientRaw().current,
				Rect(Siv3DEngine::GetWindow()->getState().clientSize));
		}

		void SetTransform(const Mat3x2& matrix) 
		{
			Siv3DEngine::GetCursor()->setTransform(matrix);
		}

		const Mat3x2& GetTransform()
		{
			return Siv3DEngine::GetCursor()->getTransform();
		}

		void ClipClientRect(bool clip)
		{
			Siv3DEngine::GetCursor()->clipClientRect(clip);
		}

		void SetStyle(const CursorStyle style)
		{
			Siv3DEngine::GetCursor()->setStyle(style);
		}

		CursorStyle GetStyle()
		{
			return Siv3DEngine::GetCursor()->getStyle();
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
