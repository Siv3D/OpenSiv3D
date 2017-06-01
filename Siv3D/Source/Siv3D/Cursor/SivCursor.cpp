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
# include <Siv3D/Geometry2D.hpp>
# include <Siv3D/Window.hpp>

namespace s3d
{
	namespace Cursor
	{
		Point Pos()
		{
			return Siv3DEngine::GetCursor()->clientPos();
		}

		Vec2 PosF()
		{
			return Siv3DEngine::GetCursor()->clientPos();
		}

		Point PreviousPos()
		{
			return Siv3DEngine::GetCursor()->previousClientPos();
		}

		Vec2 PreviousPosF()
		{
			return Siv3DEngine::GetCursor()->previousClientPos();
		}

		Point Delta()
		{
			return Siv3DEngine::GetCursor()->clientDelta();
		}

		Vec2 DeltaF()
		{
			return Siv3DEngine::GetCursor()->clientDelta();
		}

		Point ScreenPos()
		{
			return Siv3DEngine::GetCursor()->screenPos();
		}

		Point PreviousScreenPos()
		{
			return Siv3DEngine::GetCursor()->previousScreenPos();
		}

		Point ScreenDelta()
		{
			return Siv3DEngine::GetCursor()->screenDelta();
		}

		void SetPos(const int32 x, const int32 y)
		{
			Siv3DEngine::GetCursor()->setPos(x, y);
		}

		bool OnClientRect()
		{
			return Geometry2D::Intersect(Siv3DEngine::GetCursor()->clientPos(),
				Rect(Siv3DEngine::GetWindow()->getState().clientSize));
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
