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
# include <Siv3D/Common.hpp>
# include <Siv3D/FontStyle.hpp>
# include <Siv3D/GlyphInfo.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Image.hpp>

extern "C"
{
# include <ft2build.h>
# include FT_FREETYPE_H
# include FT_GLYPH_H
# include FT_OUTLINE_H
# include FT_SYNTHESIS_H
}

# include <ThirdParty/msdfgen/msdfgen.h>

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
	bool LoadGlyph(FT_Face face, GlyphIndex glyphIndex, const FontStyle style);

	[[nodiscard]]
	GlyphBBox GetGlyphBound(FT_Face face);

	[[nodiscard]]
	GlyphBBox GetGlyphBound(const msdfgen::Shape& shape);

	[[nodiscard]]
	Array<LineString> GetGlyphOutline(FT_Face face, GlyphBBox& bbox, CloseRing closeRing);

	[[nodiscard]]
	Image RenderSDF(const std::vector<uint8>& bitmap, int32 imageWidth, int32 imageHeight);

	[[nodiscard]]
	bool GetShape(FT_Face face, msdfgen::Shape& shape);

	[[nodiscard]]
	Image RenderMSDF(const msdfgen::Bitmap<float, 3>& bitmap);
}
