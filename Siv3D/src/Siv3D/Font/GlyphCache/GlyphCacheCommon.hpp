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
# include <Siv3D/Common.hpp>
# include <Siv3D/GlyphInfo.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Char.hpp>
# include "../FontData.hpp"

namespace s3d
{
	struct GlyphCache
	{
		GlyphInfo info;

		int16 textureRegionLeft = 0;

		int16 textureRegionTop = 0;

		int16 textureRegionWidth = 0;

		int16 textureRegionHeight = 0;
	};

	struct BufferImage
	{
		static constexpr int32 MaxImageHeight = 4096;

		Image image;

		Color backgroundColor{ 255, 0 };

		int32 bufferWidth = 2;

		int32 padding = 1;

		Point penPos = { 0, padding };

		int32 currentMaxHeight = 0;
	};

	[[nodiscard]]
	double GetTabAdvance(double spaceWidth, double scale, double baseX, double currentX, int32 indentSize);

	[[nodiscard]]
	bool ProcessControlCharacter(char32 ch, Vec2& penPos, int32& line, const Vec2& basePos, double scale, double lineHeightScale, const FontFaceProperty& prop);

	[[nodiscard]]
	bool CacheGlyph(const FontData& font, const Image& image, const GlyphInfo& glyphInfo,
		BufferImage& buffer, HashTable<GlyphIndex, GlyphCache>& glyphTable);
}
