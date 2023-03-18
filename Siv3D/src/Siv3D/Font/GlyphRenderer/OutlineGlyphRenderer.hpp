//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/OutlineGlyph.hpp>
# include <Siv3D/PredefinedYesNo.hpp>

struct FT_FaceRec_;
typedef struct FT_FaceRec_* FT_Face;

namespace s3d
{
	struct FontFaceProperty;

	[[nodiscard]]
	OutlineGlyph RenderOutlineGlyph(FT_Face face, GlyphIndex glyphIndex, CloseRing closeRing, const FontFaceProperty& prop);
}
