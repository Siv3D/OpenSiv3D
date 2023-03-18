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
# include <Siv3D/StringView.hpp>
# include <Siv3D/BitmapGlyph.hpp>
# include <Siv3D/SDFGlyph.hpp>
# include <Siv3D/MSDFGlyph.hpp>
# include "FontFace.hpp"

namespace s3d
{
	class IconData
	{
	public:

		IconData() = default;

		IconData(FT_Library library, FilePathView path, size_t faceIndex);

		~IconData();

		[[nodiscard]]
		bool isInitialized() const noexcept;

		[[nodiscard]]
		bool hasGlyph(char32 codePoint);

		[[nodiscard]]
		GlyphIndex getGlyphIndex(char32 codePoint);

		[[nodiscard]]
		BitmapGlyph renderBitmap(GlyphIndex glyphIndex, int32 fontPixelSize);

		[[nodiscard]]
		SDFGlyph renderSDF(GlyphIndex glyphIndex, int32 fontPixelSize, int32 buffer);

		[[nodiscard]]
		MSDFGlyph renderMSDF(GlyphIndex glyphIndex, int32 fontPixelSize, int32 buffer);

	private:

		FT_Face m_face = nullptr;

		FontFaceProperty m_property;

		bool m_initialized = false;
	};
}
