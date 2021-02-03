//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"

namespace s3d
{
	using GlyphIndex = uint32;

	struct GlyphInfo
	{
		GlyphIndex glyphIndex = 0;

		int32 xAdvance = 0;

		int32 yAdvance = 0;
	};
}
