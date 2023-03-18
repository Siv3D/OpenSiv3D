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
# include <Siv3D/Font.hpp>
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

		FontData(FT_Library library, FilePathView path, size_t faceIndex, FontMethod fontMethod, int32 fontSize, FontStyle style);

		~FontData();

		[[nodiscard]]
		bool isInitialized() const noexcept;

		void setIndentSize(int32 indentSize) noexcept;

		[[nodiscard]]
		const FontFaceProperty& getProperty() const noexcept;
		
		[[nodiscard]]
		FontMethod getMethod() const;

		[[nodiscard]]
		bool hasGlyph(StringView ch);

		[[nodiscard]]
		GlyphIndex getGlyphIndex(StringView ch);

		[[nodiscard]]
		Array<GlyphCluster> getGlyphClusters(StringView s, bool recursive, Ligature ligature) const;

		[[nodiscard]]
		GlyphInfo getGlyphInfoByGlyphIndex(GlyphIndex glyphIndex) const;

		[[nodiscard]]
		OutlineGlyph renderOutlineByGlyphIndex(GlyphIndex glyphIndex, CloseRing closeRing) const;

		[[nodiscard]]
		Array<OutlineGlyph> renderOutlines(StringView s, CloseRing closeRing, Ligature ligature) const;

		[[nodiscard]]
		PolygonGlyph renderPolygonByGlyphIndex(GlyphIndex glyphIndex) const;

		[[nodiscard]]
		Array<PolygonGlyph> renderPolygons(StringView s, Ligature ligature) const;

		[[nodiscard]]
		BitmapGlyph renderBitmapByGlyphIndex(GlyphIndex glyphIndex) const;

		[[nodiscard]]
		SDFGlyph renderSDFByGlyphIndex(GlyphIndex glyphIndex, int32 buffer) const;

		[[nodiscard]]
		MSDFGlyph renderMSDFByGlyphIndex(GlyphIndex glyphIndex, int32 buffer) const;

		[[nodiscard]]
		IGlyphCache& getGlyphCache() const;

		[[nodiscard]]
		bool addFallbackFont(const std::weak_ptr<AssetHandle<Font>::AssetIDWrapperType>& font);
		
		[[nodiscard]]
		const std::weak_ptr<AssetHandle<Font>::AssetIDWrapperType>& getFallbackFont(size_t index) const;

	private:

	# if SIV3D_PLATFORM(WINDOWS)

		FontResourceHolder m_resource;

	# endif

		FontFace m_fontFace;

		Array<std::weak_ptr<AssetHandle<Font>::AssetIDWrapperType>> m_fallbackFonts;

		FontMethod m_method = FontMethod::Bitmap;

		std::unique_ptr<IGlyphCache> m_glyphCache;

		bool m_initialized = false;
	};
}
