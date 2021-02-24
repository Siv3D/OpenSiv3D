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

# include <Siv3D/Font.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CFont_Headless.hpp"
# include "GlyphCache/IGlyphCache.hpp"
# include "FontCommon.hpp"

namespace s3d
{
	CFont_Headless::CFont_Headless()
	{
		// do nothing
	}

	CFont_Headless::~CFont_Headless()
	{
		LOG_SCOPED_TRACE(U"CFont_Headless::~CFont_Headless()");

		m_fonts.destroy();

		if (m_freeType)
		{
			FT_Done_FreeType(m_freeType);
		}
	}

	void CFont_Headless::init()
	{
		LOG_SCOPED_TRACE(U"CFont_Headless::init()");

		if (const FT_Error error = FT_Init_FreeType(&m_freeType))
		{
			throw EngineError{ U"FT_Init_FreeType() failed" };
		}

		// null Font を管理に登録
		{
			// null Font を作成
			auto nullFont = std::make_unique<FontData>(FontData::Null{});

			if (not nullFont->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError(U"Null Font initialization failed");
			}

			// 管理に登録
			m_fonts.setNullData(std::move(nullFont));
		}

		// エンジンフォントの展開
		{
			if (not detail::ExtractEngineFonts())
			{
				throw EngineError(U"CFont::init(): Failed to extract font files");
			}
		}

		// デフォルト絵文字
		{
			m_defaultEmoji = detail::CreateDefaultEmoji(m_freeType);
		}
	}

	Font::IDType CFont_Headless::create(const FilePathView path, const size_t faceIndex, const FontMethod fontMethod, const int32 fontSize, const FontStyle style)
	{
		// Font を作成
		auto font = std::make_unique<FontData>(m_freeType, path, faceIndex, fontMethod, fontSize, style);

		if (not font->isInitialized()) // もし作成に失敗していたら
		{
			return Font::IDType::NullAsset();
		}

		const auto& prop = font->getProperty();
		const String fontName = (prop.styleName) ? (prop.familiyName + U' ' + prop.styleName) : (prop.familiyName);
		const String info = U"(`{0}`, size: {1}, style: {2}, ascender: {3}, descender: {4})"_fmt(fontName, prop.fontPixelSize, detail::ToString(prop.style), prop.ascender, prop.descender);

		// Font を管理に登録
		return m_fonts.add(std::move(font), info);
	}

	Font::IDType CFont_Headless::create(const Typeface typeface, const FontMethod fontMethod, const int32 fontSize, const FontStyle style)
	{
		const detail::TypefaceInfo info = detail::GetTypefaceInfo(typeface);

		return create(info.path, info.faceIndex, fontMethod, fontSize, style);
	}

	void CFont_Headless::release(const Font::IDType handleID)
	{
		m_fonts.erase(handleID);
	}

	bool CFont_Headless::addFallbackFont(const Font::IDType handleID, const std::weak_ptr<AssetHandle<Font>::AssetIDWrapperType>& font)
	{
		return m_fonts[handleID]->addFallbackFont(font);
	}

	const FontFaceProperty& CFont_Headless::getProperty(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getProperty();
	}

	FontMethod CFont_Headless::getMethod(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getMethod();
	}

	void CFont_Headless::setBufferThickness(const Font::IDType handleID, const int32 thickness)
	{
		return m_fonts[handleID]->getGlyphCache().setBufferWidth(thickness);
	}

	int32 CFont_Headless::getBufferThickness(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getGlyphCache().getBufferWidth();
	}

	bool CFont_Headless::hasGlyph(const Font::IDType handleID, StringView ch)
	{
		return m_fonts[handleID]->hasGlyph(ch);
	}

	GlyphIndex CFont_Headless::getGlyphIndex(const Font::IDType handleID, const StringView ch)
	{
		return m_fonts[handleID]->getGlyphIndex(ch);
	}

	Array<GlyphCluster> CFont_Headless::getGlyphClusters(const Font::IDType handleID, const StringView s, const bool recursive)
	{
		return m_fonts[handleID]->getGlyphClusters(s, recursive);
	}

	GlyphInfo CFont_Headless::getGlyphInfo(const Font::IDType handleID, const StringView ch)
	{
		const auto& font = m_fonts[handleID];

		return font->getGlyphInfoByGlyphIndex(font->getGlyphIndex(ch));
	}

	OutlineGlyph CFont_Headless::renderOutline(const Font::IDType handleID, const StringView ch, const CloseRing closeRing)
	{
		const auto& font = m_fonts[handleID];

		return font->renderOutlineByGlyphIndex(font->getGlyphIndex(ch), closeRing);
	}

	OutlineGlyph CFont_Headless::renderOutlineByGlyphIndex(const Font::IDType handleID, const GlyphIndex glyphIndex, const CloseRing closeRing)
	{
		return m_fonts[handleID]->renderOutlineByGlyphIndex(glyphIndex, closeRing);
	}

	Array<OutlineGlyph> CFont_Headless::renderOutlines(const Font::IDType handleID, const StringView s, const CloseRing closeRing)
	{
		return m_fonts[handleID]->renderOutlines(s, closeRing);
	}

	BitmapGlyph CFont_Headless::renderBitmap(const Font::IDType handleID, const StringView s)
	{
		const auto& font = m_fonts[handleID];

		return font->renderBitmapByGlyphIndex(font->getGlyphIndex(s));
	}

	BitmapGlyph CFont_Headless::renderBitmapByGlyphIndex(const Font::IDType handleID, const GlyphIndex glyphIndex)
	{
		return m_fonts[handleID]->renderBitmapByGlyphIndex(glyphIndex);
	}

	SDFGlyph CFont_Headless::renderSDF(const Font::IDType handleID, const StringView s, const int32 buffer)
	{
		const auto& font = m_fonts[handleID];

		return font->renderSDFByGlyphIndex(font->getGlyphIndex(s), buffer);
	}

	SDFGlyph CFont_Headless::renderSDFByGlyphIndex(const Font::IDType handleID, const GlyphIndex glyphIndex, const int32 buffer)
	{
		return m_fonts[handleID]->renderSDFByGlyphIndex(glyphIndex, buffer);
	}

	MSDFGlyph CFont_Headless::renderMSDF(const Font::IDType handleID, const StringView s, const int32 buffer)
	{
		const auto& font = m_fonts[handleID];

		return font->renderMSDFByGlyphIndex(font->getGlyphIndex(s), buffer);
	}

	MSDFGlyph CFont_Headless::renderMSDFByGlyphIndex(const Font::IDType handleID, const GlyphIndex glyphIndex, const int32 buffer)
	{
		return m_fonts[handleID]->renderMSDFByGlyphIndex(glyphIndex, buffer);
	}

	bool CFont_Headless::preload(const Font::IDType handleID, const StringView chars)
	{
		const auto& font = m_fonts[handleID];

		return font->getGlyphCache().preload(*font, chars);
	}

	const Texture& CFont_Headless::getTexture(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getGlyphCache().getTexture();
	}

	Array<double> CFont_Headless::getXAdvances(const Font::IDType handleID, const StringView s, const Array<GlyphCluster>& clusters)
	{
		const auto& font = m_fonts[handleID];
		{
			return m_fonts[handleID]->getGlyphCache().getXAdvances(*font, s, clusters);
		}
	}

	RectF CFont_Headless::region(const Font::IDType handleID, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double fontSize, const double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		{
			return m_fonts[handleID]->getGlyphCache().region(*font, s, clusters, false, pos, fontSize, lineHeightScale);
		}
	}

	RectF CFont_Headless::regionBase(const Font::IDType handleID, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double fontSize, const double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		{
			return m_fonts[handleID]->getGlyphCache().region(*font, s, clusters, true, pos, fontSize, lineHeightScale);
		}
	}

	RectF CFont_Headless::draw(const Font::IDType handleID, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double fontSize, const TextStyle&, const ColorF&, const double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		{
			return m_fonts[handleID]->getGlyphCache().region(*font, s, clusters, false, pos, fontSize, lineHeightScale);
		}
	}

	bool CFont_Headless::draw(const Font::IDType, const StringView, const Array<GlyphCluster>&, const RectF&, const double, const TextStyle&, const ColorF&, const double)
	{
		// [Siv3D ToDo]
		return false;
	}

	RectF CFont_Headless::drawBase(const Font::IDType handleID, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double fontSize, const TextStyle&, const ColorF&, const double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		{
			return m_fonts[handleID]->getGlyphCache().region(*font, s, clusters, true, pos, fontSize, lineHeightScale);
		}
	}

	RectF CFont_Headless::drawFallback(const Font::IDType handleID, const GlyphCluster& cluster, const Vec2& pos, const double fontSize, const TextStyle&, const ColorF&, const double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		{
			return m_fonts[handleID]->getGlyphCache().regionFallback(*font, cluster, false, pos, fontSize, lineHeightScale);
		}
	}

	RectF CFont_Headless::drawBaseFallback(const Font::IDType handleID, const GlyphCluster& cluster, const Vec2& pos, const double fontSize, const TextStyle&, const ColorF&, const double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		{
			return m_fonts[handleID]->getGlyphCache().regionFallback(*font, cluster, true, pos, fontSize, lineHeightScale);
		}
	}

	RectF CFont_Headless::regionFallback(const Font::IDType handleID, const GlyphCluster& cluster, const Vec2& pos, const double fontSize, double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		{
			return m_fonts[handleID]->getGlyphCache().regionFallback(*font, cluster, false, pos, fontSize, lineHeightScale);
		}
	}

	RectF CFont_Headless::regionBaseFallback(const Font::IDType handleID, const GlyphCluster& cluster, const Vec2& pos, const double fontSize, double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		{
			return m_fonts[handleID]->getGlyphCache().regionFallback(*font, cluster, true, pos, fontSize, lineHeightScale);
		}
	}

	double CFont_Headless::xAdvanceFallback(const Font::IDType handleID, const GlyphCluster& cluster)
	{
		const auto& font = m_fonts[handleID];
		{
			return m_fonts[handleID]->getGlyphCache().xAdvanceFallback(*font, cluster);
		}
	}


	bool CFont_Headless::hasEmoji(const StringView emoji)
	{
		return m_defaultEmoji->hasGlyph(emoji);
	}

	GlyphIndex CFont_Headless::getEmojiGlyphIndex(const StringView emoji)
	{
		return m_defaultEmoji->getGlyphIndex(emoji);
	}

	Image CFont_Headless::renderEmojiBitmap(const GlyphIndex glyphIndex)
	{
		return m_defaultEmoji->renderBitmap(glyphIndex).image;
	}
}
