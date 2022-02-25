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
# include "GlyphInfo.hpp"
# include "TextureRegion.hpp"

namespace s3d
{
	struct Glyph : GlyphInfo
	{
		TextureRegion texture;

		char32 codePoint = U'\0';

		SIV3D_NODISCARD_CXX20
		Glyph() = default;

		SIV3D_NODISCARD_CXX20
		explicit Glyph(const GlyphInfo& glyphInfo);
	};
}

# include "detail/Glyph.ipp"
