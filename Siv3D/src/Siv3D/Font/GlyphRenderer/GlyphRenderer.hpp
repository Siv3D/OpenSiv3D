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
# include <Siv3D/MathConstants.hpp>
# include <Siv3D/FontStyle.hpp>
# include <Siv3D/FontMethod.hpp>
# include <Siv3D/GlyphInfo.hpp>
# include "../FontFaceProperty.hpp"

struct FT_FaceRec_;
typedef struct FT_FaceRec_* FT_Face;

namespace s3d
{
	struct GlyphBBox
	{
		double xMin = Math::Inf;
		double yMin = Math::Inf;
		double xMax = -Math::Inf;
		double yMax = -Math::Inf;
	};

	[[nodiscard]]
	bool LoadOutlineGlyph(FT_Face face, GlyphIndex glyphIndex, const FontStyle style);

	[[nodiscard]]
	GlyphBBox GetOutlineGlyphBound(FT_Face face);

	[[nodiscard]]
	GlyphInfo GetGlyphInfo(FT_Face face, GlyphIndex glyphIndex, const FontFaceProperty& prop, FontMethod method);
}
