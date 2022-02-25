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

namespace s3d
{
	constexpr Vec2 GlyphInfo::getOffset(const double scale) const noexcept
	{
		return{ ((left - buffer) * scale), ((ascender - top - buffer) * scale) };
	}

	constexpr Vec2 GlyphInfo::getBase(const double scale) const noexcept
	{
		return{ ((left - buffer) * scale), ((-top - buffer) * scale) };
	}
}
