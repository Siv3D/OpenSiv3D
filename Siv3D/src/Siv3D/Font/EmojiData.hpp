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
# include "FontFace.hpp"

namespace s3d
{
	class EmojiData
	{
	public:

		EmojiData() = default;

		EmojiData(FT_Library library, FilePathView path, size_t faceIndex);

		~EmojiData();

		[[nodiscard]]
		bool isInitialized() const noexcept;

		[[nodiscard]]
		bool hasGlyph(StringView ch);

		[[nodiscard]]
		GlyphIndex getGlyphIndex(StringView ch);

		[[nodiscard]]
		BitmapGlyph renderBitmap(GlyphIndex glyphIndex);

	private:

		FT_Face m_face = nullptr;

		hb_font_t* m_hbFont = nullptr;

		hb_buffer_t* m_hbBuffer = nullptr;

		FontFaceProperty m_property;

		bool m_initialized = false;
	};
}
