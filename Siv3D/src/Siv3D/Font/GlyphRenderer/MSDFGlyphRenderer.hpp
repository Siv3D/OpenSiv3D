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
# include <Siv3D/MSDFGlyph.hpp>

struct FT_FaceRec_;
typedef struct FT_FaceRec_* FT_Face;

namespace s3d
{
	struct FontFaceProperty;

	[[nodiscard]]
	MSDFGlyph RenderMSDFGlyph(FT_Face face, GlyphIndex glyphIndex, int32 buffer, const FontFaceProperty& prop);
}
