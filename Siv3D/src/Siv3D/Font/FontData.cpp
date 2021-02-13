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

# include <Siv3D/FileSystem.hpp>
# include "FontData.hpp"
# include "GlyphRenderer/GlyphRenderer.hpp"
# include "GlyphRenderer/BitmapGlyphRenderer.hpp"
# include "GlyphRenderer/OutlineGlyphRenderer.hpp"
# include "GlyphRenderer/SDFGlyphRenderer.hpp"
# include "GlyphRenderer/MSDFGlyphRenderer.hpp"
# include "GlyphCache/BitmapGlyphCache.hpp"
# include "GlyphCache/SDFGlyphCache.hpp"
# include "GlyphCache/MSDFGlyphCache.hpp"

namespace s3d
{
	FontData::FontData(Null)
	{
		m_glyphCache = std::make_unique<BitmapGlyphCache>();

		m_initialized = true;
	}

	FontData::FontData(const FT_Library library, const FilePathView path, const size_t faceIndex, const FontMethod fontMethod, const int32 fontSize, const FontStyle style)
	{
	# if SIV3D_PLATFORM(WINDOWS)

		if (FileSystem::IsResource(path))
		{
			m_resource = FontResourceHolder{ path };

			if (not m_fontFace.load(library, m_resource.data(), m_resource.size(), faceIndex, fontSize, style))
			{
				return;
			}
		}
		else
		{
			if (not m_fontFace.load(library, path, faceIndex, fontSize, style))
			{
				return;
			}
		}

	# else

		if (not m_fontFace.load(library, path, faceIndex, fontSize, style))
		{
			return;
		}

	# endif

		switch (fontMethod)
		{
		case FontMethod::Bitmap:
			m_glyphCache = std::make_unique<BitmapGlyphCache>();
			break;
		case FontMethod::SDF:
			m_glyphCache = std::make_unique<SDFGlyphCache>();
			break;
		case FontMethod::MSDF:
			m_glyphCache = std::make_unique<MSDFGlyphCache>();
			break;
		}

		m_method = fontMethod;

		m_initialized = true;
	}

	FontData::~FontData()
	{

	}

	bool FontData::isInitialized() const noexcept
	{
		return m_initialized;
	}

	const FontFaceProperty& FontData::getProperty() const noexcept
	{
		return m_fontFace.getProperty();
	}

	FontMethod FontData::getMethod() const
	{
		return m_method;
	}

	bool FontData::hasGlyph(const StringView ch)
	{
		const HBGlyphInfo glyphInfo = m_fontFace.getHBGlyphInfo(ch);

		if (glyphInfo.count != 1)
		{
			return false;
		}
		
		const GlyphIndex glyphIndex = glyphInfo.info[0].codepoint;

		return (glyphIndex != 0);
	}

	GlyphIndex FontData::getGlyphIndex(const StringView ch)
	{
		const HBGlyphInfo glyphInfo = m_fontFace.getHBGlyphInfo(ch);

		if (glyphInfo.count != 1)
		{
			return 0;
		}

		const GlyphIndex glyphIndex = glyphInfo.info[0].codepoint;

		return glyphIndex;
	}

	Array<GlyphCluster> FontData::getGlyphClusters(const StringView s) const
	{
		const HBGlyphInfo glyphInfo = m_fontFace.getHBGlyphInfo(s);

		const size_t count = glyphInfo.count;

		Array<GlyphCluster> clusters(count);

		for (size_t i = 0; i < count; ++i)
		{
			clusters[i] = { glyphInfo.info[i].codepoint, glyphInfo.info[i].cluster };
		}

		return clusters;
	}

	GlyphInfo FontData::getGlyphInfoByGlyphIndex(const GlyphIndex glyphIndex) const
	{
		return GetGlyphInfo(m_fontFace.getFT_Face(), glyphIndex, m_fontFace.getProperty());
	}

	OutlineGlyph FontData::renderOutlineByGlyphIndex(const GlyphIndex glyphIndex, const CloseRing closeRing) const
	{
		return RenderOutlineGlyph(m_fontFace.getFT_Face(), glyphIndex, closeRing, m_fontFace.getProperty());
	}

	Array<OutlineGlyph> FontData::renderOutlines(const StringView s, const CloseRing closeRing) const
	{
		const HBGlyphInfo glyphInfo = m_fontFace.getHBGlyphInfo(s);

		Array<OutlineGlyph> results(Arg::reserve = glyphInfo.count);

		for (size_t i = 0; i < glyphInfo.count; ++i)
		{
			const GlyphIndex glyphIndex = glyphInfo.info[i].codepoint;

			results << RenderOutlineGlyph(m_fontFace.getFT_Face(), glyphIndex, closeRing, m_fontFace.getProperty());
		}

		return results;
	}

	BitmapGlyph FontData::renderBitmapByGlyphIndex(const GlyphIndex glyphIndex) const
	{
		return RenderBitmapGlyph(m_fontFace.getFT_Face(), glyphIndex, m_fontFace.getProperty());
	}

	SDFGlyph FontData::renderSDFByGlyphIndex(const GlyphIndex glyphIndex, const int32 buffer) const
	{
		return RenderSDFGlyph(m_fontFace.getFT_Face(), glyphIndex, buffer, m_fontFace.getProperty());
	}

	MSDFGlyph FontData::renderMSDFByGlyphIndex(const GlyphIndex glyphIndex, const int32 buffer) const
	{
		return RenderMSDFGlyph(m_fontFace.getFT_Face(), glyphIndex, buffer, m_fontFace.getProperty());
	}

	IGlyphCache& FontData::getGlyphCache()
	{
		return *m_glyphCache;
	}
}
