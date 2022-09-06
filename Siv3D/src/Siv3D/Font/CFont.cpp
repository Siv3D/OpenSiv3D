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

# include <Siv3D/Font.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/Graphics2D.hpp>
# include <Siv3D/OutlineGlyph.hpp>
# include <Siv3D/PolygonGlyph.hpp>
# include <Siv3D/MeshGlyph.hpp>
# include <Siv3D/ScopedCustomShader2D.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CFont.hpp"
# include "GlyphCache/IGlyphCache.hpp"
# include "FontCommon.hpp"

namespace s3d
{
	CFont::CFont()
	{
		// do nothing
	}

	CFont::~CFont()
	{
		LOG_SCOPED_TRACE(U"CFont::~CFont()");

		m_defaultIcons.clear();

		m_defaultEmoji.reset();

		m_fonts.destroy();

		if (m_freeType)
		{
			FT_Done_FreeType(m_freeType);
		}
	}

	void CFont::init()
	{
		LOG_SCOPED_TRACE(U"CFont::init()");

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

		// フォント用シェーダ
		{
			m_shader = std::make_unique<FontShader>();

			// Bitmap Font
			m_shader->shaders[0]	= HLSL{ Resource(U"engine/shader/d3d11/bitmapfont.ps") }
									| GLSL{ Resource(U"engine/shader/glsl/bitmapfont.frag"), { { U"PSConstants2D", 0 } } }
									| ESSL{ Resource(U"engine/shader/essl/bitmapfont.frag"), { { U"PSConstants2D", 0 } } }
									| WGSL{ Resource(U"engine/shader/wgsl/bitmapfont.frag.wgsl"), { { U"PSConstants2D", 0 } } }
									| MSL{ U"PS_Shape" }; // [Siv3D Todo]

			// Color Bitmap Font
			m_shader->shaders[1]	= HLSL{ Resource(U"engine/shader/d3d11/texture.ps") }
									| GLSL{ Resource(U"engine/shader/glsl/texture.frag"), { { U"PSConstants2D", 0 } } }
									| ESSL{ Resource(U"engine/shader/essl/texture.frag"), { { U"PSConstants2D", 0 } } }
									| WGSL{ Resource(U"engine/shader/wgsl/texture.frag.wgsl"), { { U"PSConstants2D", 0 } } }
									| MSL{ U"PS_Shape" }; // [Siv3D Todo]

			// SDF Font
			m_shader->shaders[2]	= HLSL{ Resource(U"engine/shader/d3d11/sdffont.ps") }
									| GLSL{ Resource(U"engine/shader/glsl/sdffont.frag"), { { U"PSConstants2D", 0 } } }
									| ESSL{ Resource(U"engine/shader/essl/sdffont.frag"), { { U"PSConstants2D", 0 } } }
									| WGSL{ Resource(U"engine/shader/wgsl/sdffont.frag.wgsl"), { { U"PSConstants2D", 0 } } }
									| MSL{ U"PS_Shape" }; // [Siv3D Todo]

			// SDF Font (Outline)
			m_shader->shaders[3]	= HLSL{ Resource(U"engine/shader/d3d11/sdffont_outline.ps") }
									| GLSL{ Resource(U"engine/shader/glsl/sdffont_outline.frag"), { { U"PSConstants2D", 0 } } }
									| ESSL{ Resource(U"engine/shader/essl/sdffont_outline.frag"), { { U"PSConstants2D", 0 } } }
									| WGSL{ Resource(U"engine/shader/wgsl/sdffont_outline.frag.wgsl"), { { U"PSConstants2D", 0 } } }
									| MSL{ U"PS_Shape" }; // [Siv3D Todo]

			// SDF Font (Shadow)
			m_shader->shaders[4]	= HLSL{ Resource(U"engine/shader/d3d11/sdffont_shadow.ps") }
									| GLSL{ Resource(U"engine/shader/glsl/sdffont_shadow.frag"), { { U"PSConstants2D", 0 } } }
									| ESSL{ Resource(U"engine/shader/essl/sdffont_shadow.frag"), { { U"PSConstants2D", 0 } } }
									| WGSL{ Resource(U"engine/shader/wgsl/sdffont_shadow.frag.wgsl"), { { U"PSConstants2D", 0 } } }
									| MSL{ U"PS_Shape" }; // [Siv3D Todo]

			// SDF Font (Outline + Shadow)
			m_shader->shaders[5]	= HLSL{ Resource(U"engine/shader/d3d11/sdffont_outlineshadow.ps") }
									| GLSL{ Resource(U"engine/shader/glsl/sdffont_outlineshadow.frag"), { { U"PSConstants2D", 0 } } }
									| ESSL{ Resource(U"engine/shader/essl/sdffont_outlineshadow.frag"), { { U"PSConstants2D", 0 } } }
									| WGSL{ Resource(U"engine/shader/wgsl/sdffont_outlineshadow.frag.wgsl"), { { U"PSConstants2D", 0 } } }
									| MSL{ U"PS_Shape" }; // [Siv3D Todo]

			// MSDF Font
			m_shader->shaders[6]	= HLSL{ Resource(U"engine/shader/d3d11/msdffont.ps") }
									| GLSL{ Resource(U"engine/shader/glsl/msdffont.frag"), { { U"PSConstants2D", 0 } } }
									| ESSL{ Resource(U"engine/shader/essl/msdffont.frag"), { { U"PSConstants2D", 0 } } }
									| WGSL{ Resource(U"engine/shader/wgsl/msdffont.frag.wgsl"), { { U"PSConstants2D", 0 } } }
									| MSL{ U"PS_Shape" }; // [Siv3D Todo]

			// MSDF Font (Outline)
			m_shader->shaders[7]	= HLSL{ Resource(U"engine/shader/d3d11/msdffont_outline.ps") }
									| GLSL{ Resource(U"engine/shader/glsl/msdffont_outline.frag"), { { U"PSConstants2D", 0 } } }
									| ESSL{ Resource(U"engine/shader/essl/msdffont_outline.frag"), { { U"PSConstants2D", 0 } } }
									| WGSL{ Resource(U"engine/shader/wgsl/msdffont_outline.frag.wgsl"), { { U"PSConstants2D", 0 } } }
									| MSL{ U"PS_Shape" }; // [Siv3D Todo]

			// MSDF Font (Shadow)
			m_shader->shaders[8]	= HLSL{ Resource(U"engine/shader/d3d11/msdffont_shadow.ps") }
									| GLSL{ Resource(U"engine/shader/glsl/msdffont_shadow.frag"), { { U"PSConstants2D", 0 } } }
									| ESSL{ Resource(U"engine/shader/essl/msdffont_shadow.frag"), { { U"PSConstants2D", 0 } } }
									| WGSL{ Resource(U"engine/shader/wgsl/msdffont_shadow.frag.wgsl"), { { U"PSConstants2D", 0 } } }
									| MSL{ U"PS_Shape" }; // [Siv3D Todo]

			// MSDF Font (Outline + Shadow)
			m_shader->shaders[9]	= HLSL{ Resource(U"engine/shader/d3d11/msdffont_outlineshadow.ps") }
									| GLSL{ Resource(U"engine/shader/glsl/msdffont_outlineshadow.frag"), { { U"PSConstants2D", 0 } } }
									| ESSL{ Resource(U"engine/shader/essl/msdffont_outlineshadow.frag"), { { U"PSConstants2D", 0 } } }
									| WGSL{ Resource(U"engine/shader/wgsl/msdffont_outlineshadow.frag.wgsl"), { { U"PSConstants2D", 0 } } }
									| MSL{ U"PS_Shape" }; // [Siv3D Todo]

			for (const auto& shader : m_shader->shaders)
			{
				if (not shader)
				{
					throw EngineError{ U"CFont::init(): Failed to load font shaders" };
				}
			}
		}

		// エンジンフォントの展開
		{
			if (not detail::ExtractEngineFonts())
			{
				throw EngineError{ U"CFont::init(): Failed to extract font files" };
			}
		}

		// デフォルト絵文字
		{
			m_defaultEmoji = detail::CreateDefaultEmoji(m_freeType);

			if (not m_defaultEmoji->isInitialized())
			{
				LOG_INFO(U"CFont::init(): Failed to create default emojis");
			}
		}

		// デフォルトアイコン
		{
			m_defaultIcons << detail::CreateDefaultIcon(m_freeType, Typeface::Icon_Awesome_Solid);
			m_defaultIcons << detail::CreateDefaultIcon(m_freeType, Typeface::Icon_Awesome_Brand);
			m_defaultIcons << detail::CreateDefaultIcon(m_freeType, Typeface::Icon_MaterialDesign);

			if (not m_defaultIcons.all([](const std::unique_ptr<IconData>& d) { return d->isInitialized(); }))
			{
				LOG_INFO(U"CFont::init(): Failed to create default icons");
			}
		}
	}

	size_t CFont::getFontCount() const
	{
		return m_fonts.size();
	}

	Font::IDType CFont::create(const FilePathView path, const size_t faceIndex, const FontMethod fontMethod, const int32 fontSize, const FontStyle style)
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

	Font::IDType CFont::create(const Typeface typeface, const FontMethod fontMethod, const int32 fontSize, const FontStyle style)
	{
		const detail::TypefaceInfo info = detail::GetTypefaceInfo(typeface);

		return create(info.path, info.faceIndex, fontMethod, fontSize, style);
	}

	void CFont::release(const Font::IDType handleID)
	{
		m_fonts.erase(handleID);
	}

	bool CFont::addFallbackFont(const Font::IDType handleID, const std::weak_ptr<AssetHandle<Font>::AssetIDWrapperType>& font)
	{
		return m_fonts[handleID]->addFallbackFont(font);
	}

	void CFont::setIndentSize(const Font::IDType handleID, const int32 indentSize)
	{
		m_fonts[handleID]->setIndentSize(indentSize);
	}

	const FontFaceProperty& CFont::getProperty(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getProperty();
	}

	FontMethod CFont::getMethod(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getMethod();
	}

	void CFont::setBufferThickness(const Font::IDType handleID, const int32 thickness)
	{
		return m_fonts[handleID]->getGlyphCache().setBufferWidth(thickness);
	}

	int32 CFont::getBufferThickness(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getGlyphCache().getBufferWidth();
	}

	bool CFont::hasGlyph(const Font::IDType handleID, StringView ch)
	{
		return m_fonts[handleID]->hasGlyph(ch);
	}

	GlyphIndex CFont::getGlyphIndex(const Font::IDType handleID, const StringView ch)
	{
		return m_fonts[handleID]->getGlyphIndex(ch);
	}

	Array<GlyphCluster> CFont::getGlyphClusters(const Font::IDType handleID, const StringView s, const bool recursive, const Ligature ligature)
	{
		return m_fonts[handleID]->getGlyphClusters(s, recursive, ligature);
	}

	GlyphInfo CFont::getGlyphInfo(const Font::IDType handleID, const StringView ch)
	{
		const auto& font = m_fonts[handleID];

		return font->getGlyphInfoByGlyphIndex(font->getGlyphIndex(ch));
	}

	GlyphInfo CFont::getGlyphInfoByGlyphIndex(const Font::IDType handleID, const GlyphIndex glyphIndex)
	{
		return m_fonts[handleID]->getGlyphInfoByGlyphIndex(glyphIndex);
	}

	OutlineGlyph CFont::renderOutline(const Font::IDType handleID, const StringView ch, const CloseRing closeRing)
	{
		const auto& font = m_fonts[handleID];

		return font->renderOutlineByGlyphIndex(font->getGlyphIndex(ch), closeRing);
	}

	OutlineGlyph CFont::renderOutlineByGlyphIndex(const Font::IDType handleID, const GlyphIndex glyphIndex, const CloseRing closeRing)
	{
		return m_fonts[handleID]->renderOutlineByGlyphIndex(glyphIndex, closeRing);
	}

	Array<OutlineGlyph> CFont::renderOutlines(const Font::IDType handleID, const StringView s, const CloseRing closeRing, const Ligature ligature)
	{
		return m_fonts[handleID]->renderOutlines(s, closeRing, ligature);
	}

	PolygonGlyph CFont::renderPolygon(const Font::IDType handleID, const StringView ch)
	{
		const auto& font = m_fonts[handleID];

		return font->renderPolygonByGlyphIndex(font->getGlyphIndex(ch));
	}

	PolygonGlyph CFont::renderPolygonByGlyphIndex(const Font::IDType handleID, const GlyphIndex glyphIndex)
	{
		return m_fonts[handleID]->renderPolygonByGlyphIndex(glyphIndex);
	}

	Array<PolygonGlyph> CFont::renderPolygons(const Font::IDType handleID, const StringView s, const Ligature ligature)
	{
		return m_fonts[handleID]->renderPolygons(s, ligature);
	}

	BitmapGlyph CFont::renderBitmap(const Font::IDType handleID, const StringView s)
	{
		const auto& font = m_fonts[handleID];

		return font->renderBitmapByGlyphIndex(font->getGlyphIndex(s));
	}

	BitmapGlyph CFont::renderBitmapByGlyphIndex(const Font::IDType handleID, const GlyphIndex glyphIndex)
	{
		return m_fonts[handleID]->renderBitmapByGlyphIndex(glyphIndex);
	}

	SDFGlyph CFont::renderSDF(const Font::IDType handleID, const StringView s, const int32 buffer)
	{
		const auto& font = m_fonts[handleID];

		return font->renderSDFByGlyphIndex(font->getGlyphIndex(s), buffer);
	}

	SDFGlyph CFont::renderSDFByGlyphIndex(const Font::IDType handleID, const GlyphIndex glyphIndex, const int32 buffer)
	{
		return m_fonts[handleID]->renderSDFByGlyphIndex(glyphIndex, buffer);
	}

	MSDFGlyph CFont::renderMSDF(const Font::IDType handleID, const StringView s, const int32 buffer)
	{
		const auto& font = m_fonts[handleID];

		return font->renderMSDFByGlyphIndex(font->getGlyphIndex(s), buffer);
	}

	MSDFGlyph CFont::renderMSDFByGlyphIndex(const Font::IDType handleID, const GlyphIndex glyphIndex, const int32 buffer)
	{
		return m_fonts[handleID]->renderMSDFByGlyphIndex(glyphIndex, buffer);
	}

	bool CFont::preload(const Font::IDType handleID, const StringView chars)
	{
		const auto& font = m_fonts[handleID];

		return font->getGlyphCache().preload(*font, chars);
	}

	const Texture& CFont::getTexture(const Font::IDType handleID)
	{
		return m_fonts[handleID]->getGlyphCache().getTexture();
	}

	Glyph CFont::getGlyph(const Font::IDType handleID, const StringView ch)
	{
		if (not ch)
		{
			return{};
		}

		const auto& font = m_fonts[handleID];
		Glyph glyph{ font->getGlyphInfoByGlyphIndex(font->getGlyphIndex(ch)) };
		glyph.codePoint = ch.front();
		glyph.texture = font->getGlyphCache().getTextureRegion(*font, glyph.glyphIndex);
		return glyph;
	}

	Array<Glyph> CFont::getGlyphs(const Font::IDType handleID, const StringView s, const Ligature ligature)
	{
		const auto& font = m_fonts[handleID];
		const Array<GlyphCluster> clusters = font->getGlyphClusters(s, false, ligature);

		Array<Glyph> glyphs(Arg::reserve = clusters.size());
		for (const auto& cluster : clusters)
		{
			Glyph glyph{ font->getGlyphInfoByGlyphIndex(cluster.glyphIndex) };
			glyph.codePoint = s[cluster.pos];
			glyph.texture = font->getGlyphCache().getTextureRegion(*font, glyph.glyphIndex);
			glyph.buffer = font->getGlyphCache().getBufferThickness(glyph.glyphIndex);
			glyphs << glyph;
		}

		return glyphs;
	}

	Array<double> CFont::getXAdvances(const Font::IDType handleID, const StringView s, const Array<GlyphCluster>& clusters, const double fontSize)
	{
		const auto& font = m_fonts[handleID];
		{
			return m_fonts[handleID]->getGlyphCache().getXAdvances(*font, s, clusters, fontSize);
		}
	}

	RectF CFont::region(const Font::IDType handleID, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double fontSize, const double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		{
			return m_fonts[handleID]->getGlyphCache().region(*font, s, clusters, false, pos, fontSize, lineHeightScale);
		}
	}

	RectF CFont::regionBase(const Font::IDType handleID, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double fontSize, const double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		{
			return m_fonts[handleID]->getGlyphCache().region(*font, s, clusters, true, pos, fontSize, lineHeightScale);
		}
	}

	RectF CFont::draw(const Font::IDType handleID, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double fontSize, const TextStyle& textStyle, const ColorF& color, const double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		const HasColor hasColor{ font->getProperty().hasColor };

		if (textStyle.type != TextStyle::Type::Default && (not hasColor))
		{
			if (font->getMethod() == FontMethod::SDF)
			{
				Graphics2D::SetSDFParameters(textStyle);
			}
			else
			{
				Graphics2D::SetMSDFParameters(textStyle);
			}
		}

		if (textStyle.type == TextStyle::Type::CustomShader)
		{
			return m_fonts[handleID]->getGlyphCache().draw(*font, s, clusters, false, pos, fontSize, textStyle, (hasColor ? ColorF{ 1.0, color.a } : color), lineHeightScale);
		}
		else
		{
			ScopedCustomShader2D ps{ m_shader->getFontShader(font->getMethod(), textStyle.type, hasColor) };
			return m_fonts[handleID]->getGlyphCache().draw(*font, s, clusters, false, pos, fontSize, textStyle, (hasColor ? ColorF{ 1.0, color.a } : color), lineHeightScale);
		}
	}

	bool CFont::draw(const Font::IDType handleID, const StringView s, const Array<GlyphCluster>& clusters, const RectF& area, double fontSize, const TextStyle& textStyle, const ColorF& color, const double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		const HasColor hasColor{ font->getProperty().hasColor };

		if (textStyle.type != TextStyle::Type::Default && (not hasColor))
		{
			if (font->getMethod() == FontMethod::SDF)
			{
				Graphics2D::SetSDFParameters(textStyle);
			}
			else
			{
				Graphics2D::SetMSDFParameters(textStyle);
			}
		}

		if (textStyle.type == TextStyle::Type::CustomShader)
		{
			return m_fonts[handleID]->getGlyphCache().draw(*font, s, clusters, area, fontSize, textStyle, (hasColor ? ColorF{ 1.0, color.a } : color), lineHeightScale);
		}
		else
		{
			ScopedCustomShader2D ps{ m_shader->getFontShader(font->getMethod(), textStyle.type, hasColor) };
			return m_fonts[handleID]->getGlyphCache().draw(*font, s, clusters, area, fontSize, textStyle, (hasColor ? ColorF{ 1.0, color.a } : color), lineHeightScale);
		}
	}

	RectF CFont::drawBase(const Font::IDType handleID, const StringView s, const Array<GlyphCluster>& clusters, const Vec2& pos, const double fontSize, const TextStyle& textStyle, const ColorF& color, const double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		const HasColor hasColor{ font->getProperty().hasColor };

		if (textStyle.type != TextStyle::Type::Default && (not hasColor))
		{
			if (font->getMethod() == FontMethod::SDF)
			{
				Graphics2D::SetSDFParameters(textStyle);
			}
			else
			{
				Graphics2D::SetMSDFParameters(textStyle);
			}
		}

		if (textStyle.type == TextStyle::Type::CustomShader)
		{
			return m_fonts[handleID]->getGlyphCache().draw(*font, s, clusters, true, pos, fontSize, textStyle, (hasColor ? ColorF{ 1.0, color.a } : color), lineHeightScale);
		}
		else
		{
			ScopedCustomShader2D ps{ m_shader->getFontShader(font->getMethod(), textStyle.type, hasColor) };
			return m_fonts[handleID]->getGlyphCache().draw(*font, s, clusters, true, pos, fontSize, textStyle, (hasColor ? ColorF{ 1.0, color.a } : color), lineHeightScale);
		}
	}

	RectF CFont::drawFallback(const Font::IDType handleID, const GlyphCluster& cluster, const Vec2& pos, const double fontSize, const TextStyle& textStyle, const ColorF& color, const double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		const HasColor hasColor{ font->getProperty().hasColor };
		
		if (textStyle.type != TextStyle::Type::Default && (not hasColor))
		{
			if (font->getMethod() == FontMethod::SDF)
			{
				Graphics2D::SetSDFParameters(textStyle);
			}
			else
			{
				Graphics2D::SetMSDFParameters(textStyle);
			}
		}

		if (textStyle.type == TextStyle::Type::CustomShader)
		{
			return m_fonts[handleID]->getGlyphCache().drawFallback(*font, cluster, false, pos, fontSize, (hasColor ? ColorF{ 1.0, color.a } : color), lineHeightScale);
		}
		else
		{
			ScopedCustomShader2D ps{ m_shader->getFontShader(font->getMethod(), textStyle.type, hasColor) };
			return m_fonts[handleID]->getGlyphCache().drawFallback(*font, cluster, false, pos, fontSize, (hasColor ? ColorF{ 1.0, color.a } : color), lineHeightScale);
		}
	}

	RectF CFont::drawBaseFallback(const Font::IDType handleID, const GlyphCluster& cluster, const Vec2& pos, const double fontSize, const TextStyle& textStyle, const ColorF& color, const double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		const HasColor hasColor{ font->getProperty().hasColor };
		
		if (textStyle.type != TextStyle::Type::Default && (not hasColor))
		{
			if (font->getMethod() == FontMethod::SDF)
			{
				Graphics2D::SetSDFParameters(textStyle);
			}
			else
			{
				Graphics2D::SetMSDFParameters(textStyle);
			}
		}

		if (textStyle.type == TextStyle::Type::CustomShader)
		{
			return m_fonts[handleID]->getGlyphCache().drawFallback(*font, cluster, true, pos, fontSize, (hasColor ? ColorF{ 1.0, color.a } : color), lineHeightScale);
		}
		else
		{
			ScopedCustomShader2D ps{ m_shader->getFontShader(font->getMethod(), textStyle.type, hasColor) };
			return m_fonts[handleID]->getGlyphCache().drawFallback(*font, cluster, true, pos, fontSize, (hasColor ? ColorF{ 1.0, color.a } : color), lineHeightScale);
		}
	}

	RectF CFont::regionFallback(const Font::IDType handleID, const GlyphCluster& cluster, const Vec2& pos, const double fontSize, double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		{
			return m_fonts[handleID]->getGlyphCache().regionFallback(*font, cluster, false, pos, fontSize, lineHeightScale);
		}
	}

	RectF CFont::regionBaseFallback(const Font::IDType handleID, const GlyphCluster& cluster, const Vec2& pos, const double fontSize, double lineHeightScale)
	{
		const auto& font = m_fonts[handleID];
		{
			return m_fonts[handleID]->getGlyphCache().regionFallback(*font, cluster, true, pos, fontSize, lineHeightScale);
		}
	}

	double CFont::xAdvanceFallback(const Font::IDType handleID, const GlyphCluster& cluster, const double fontSize)
	{
		const auto& font = m_fonts[handleID];
		{
			return m_fonts[handleID]->getGlyphCache().xAdvanceFallback(*font, cluster, fontSize);
		}
	}


	bool CFont::hasEmoji(const StringView emoji)
	{
		return m_defaultEmoji->hasGlyph(emoji);
	}

	GlyphIndex CFont::getEmojiGlyphIndex(const StringView emoji)
	{
		return m_defaultEmoji->getGlyphIndex(emoji);
	}

	Image CFont::renderEmojiBitmap(const GlyphIndex glyphIndex)
	{
		return m_defaultEmoji->renderBitmap(glyphIndex).image;
	}


	bool CFont::hasIcon(const Icon::Type iconType, const char32 codePoint)
	{
		return detail::HasIcon(m_defaultIcons, iconType, codePoint);
	}

	GlyphIndex CFont::getIconGlyphIndex(const Icon::Type iconType, const char32 codePoint)
	{
		return detail::GetIconGlyphIndex(m_defaultIcons, iconType, codePoint);
	}

	Image CFont::renderIconBitmap(const Icon::Type iconType, const char32 codePoint, const int32 fontPixelSize)
	{
		return detail::RenderIconBitmap(m_defaultIcons, iconType, codePoint, fontPixelSize);
	}

	Image CFont::renderIconSDF(const Icon::Type iconType, const char32 codePoint, const int32 fontPixelSize, const int32 buffer)
	{
		return detail::RenderIconSDF(m_defaultIcons, iconType, codePoint, fontPixelSize, buffer);
	}

	Image CFont::renderIconMSDF(const Icon::Type iconType, const char32 codePoint, const int32 fontPixelSize, const int32 buffer)
	{
		return detail::RenderIconMSDF(m_defaultIcons, iconType, codePoint, fontPixelSize, buffer);
	}

	const PixelShader& CFont::getFontShader(const FontMethod method, const TextStyle::Type type, const HasColor hasColor) const
	{
		return m_shader->getFontShader(method, type, hasColor);
	}

	bool CFont::isAvailable(const Typeface typeface) const
	{
		return detail::IsAvailable(typeface);
	}
}
