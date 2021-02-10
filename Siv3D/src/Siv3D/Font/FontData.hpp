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
# include <Siv3D/StringView.hpp>
# include <Siv3D/GlyphInfo.hpp>
# include <Siv3D/GlyphCluster.hpp>
# include <Siv3D/OutlineGlyph.hpp>
# include <Siv3D/BitmapGlyph.hpp>
# include <Siv3D/SDFGlyph.hpp>
# include <Siv3D/MSDFGlyph.hpp>
# include <Siv3D/FontMethod.hpp>
# include "FontResourceHolder.hpp"
# include "FontFace.hpp"

namespace s3d
{
	class IGlyphCache;

	class FontData
	{
	public:

		struct Null {};

		FontData() = default;

		explicit FontData(Null);

		FontData(FT_Library library, FilePathView path, FontMethod fontMethod, int32 fontSize, FontStyle style);

		~FontData();

		[[nodiscard]]
		bool isInitialized() const noexcept;

		[[nodiscard]]
		const FontFaceProperty& getProperty() const noexcept;
		
		[[nodiscard]]
		FontMethod getMethod() const;

		[[nodiscard]]
		bool hasGlyph(StringView ch);

		[[nodiscard]]
		GlyphIndex getGlyphIndex(StringView ch);

		[[nodiscard]]
		Array<GlyphCluster> getGlyphClusters(StringView s) const;

		[[nodiscard]]
		GlyphInfo getGlyphInfoByGlyphIndex(GlyphIndex glyphIndex) const;

		[[nodiscard]]
		OutlineGlyph renderOutlineByGlyphIndex(GlyphIndex glyphIndex, CloseRing closeRing) const;

		[[nodiscard]]
		Array<OutlineGlyph> renderOutlines(StringView s, CloseRing closeRing) const;

		[[nodiscard]]
		BitmapGlyph renderBitmapByGlyphIndex(GlyphIndex glyphIndex) const;

		[[nodiscard]]
		SDFGlyph renderSDFByGlyphIndex(GlyphIndex glyphIndex, int32 buffer) const;

		[[nodiscard]]
		MSDFGlyph renderMSDFByGlyphIndex(GlyphIndex glyphIndex, int32 buffer) const;

		[[nodiscard]]
		IGlyphCache& getGlyphCache();

	private:

	# if SIV3D_PLATFORM(WINDOWS)

		FontResourceHolder m_resource;

	# endif

		FontFace m_fontFace;

		FontMethod m_method = FontMethod::Bitmap;

		std::unique_ptr<IGlyphCache> m_glyphCache;

		bool m_initialized = false;
	};
}
