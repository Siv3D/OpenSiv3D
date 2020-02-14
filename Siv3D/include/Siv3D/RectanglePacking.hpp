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

# pragma once
# include <utility>
# include "Fwd.hpp"
# include "Array.hpp"
# include "Rectangle.hpp"

namespace s3d
{
	namespace RectanglePacking
	{
		[[nodiscard]] std::pair<Array<Rect>, Size> Pack(const Array<Rect>& rects, int32 maxSide);
	}
}
