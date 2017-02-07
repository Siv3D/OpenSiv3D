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
# include <Siv3D/Cursor.hpp>

namespace s3d
{
	namespace Cursor
	{
		const Point& Pos()
		{
			return Siv3DEngine::GetCursor()->clientPos();
		}

		const Point& PreviousPos()
		{
			return Siv3DEngine::GetCursor()->previousClientPos();
		}

		const Point& Delta()
		{
			return Siv3DEngine::GetCursor()->clientDelta();
		}

		const Point& ScreenPos()
		{
			return Siv3DEngine::GetCursor()->screenPos();
		}

		const Point& PreviousScreenPos()
		{
			return Siv3DEngine::GetCursor()->previousScreenPos();
		}

		const Point& ScreenDelta()
		{
			return Siv3DEngine::GetCursor()->screenDelta();
		}
	}
}
