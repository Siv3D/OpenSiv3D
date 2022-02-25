//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "2DShapes.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	struct RectanglePack
	{
		Array<Rect> rects;

		Size size = { 0, 0 };
	};

	namespace RectanglePacking
	{
		[[nodiscard]]
		RectanglePack Pack(const Array<Rect>& rects, int32 maxSide, AllowFlip allowFlip = AllowFlip::No);
	}
}
