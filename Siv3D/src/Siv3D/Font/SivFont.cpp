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
# include <Siv3D/Font/IFont.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "FontFaceProperty.hpp"

namespace s3d
{
	template <>
	AssetIDWrapper<AssetHandle<Font>>::AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			FreestandingMessageBox::ShowError(U"`Font` must be initialized after engine-setup. Please fix the C++ code.");
			std::abort();
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<Font>>::~AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = SIV3D_ENGINE(Font))
		{
			p->release(m_id);
		}
	}

	Font::Font()
		: AssetHandle{ std::make_shared<AssetIDWrapperType>() }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Font::Font(const int32 fontSize, const FilePathView path, const FontStyle style)
		: Font{ FontMethod::Bitmap, fontSize, path, style } {}

	Font::Font(const FontMethod fontMethod, const int32 fontSize, const FilePathView path, const FontStyle style)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Font)->create(path, fontMethod, fontSize, style)) } {}

	Font::~Font()
	{

	}

	const String& Font::familyName() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).familiyName;
	}

	const String& Font::styleName() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).styleName;
	}

	FontStyle Font::style() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).style;
	}

	FontMethod Font::method() const
	{
		return SIV3D_ENGINE(Font)->getMethod(m_handle->id());
	}

	int32 Font::fontSize() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).fontPixelSize;
	}

	int32 Font::ascender() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).ascender;
	}

	int32 Font::descender() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).descender;
	}

	int32 Font::height() const
	{
		const auto& prop = SIV3D_ENGINE(Font)->getProperty(m_handle->id());

		return (prop.ascender + prop.descender);
	}

	double Font::spaceWidth() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).spaceWidth;
	}

	void Font::setBufferThickness(const int32 thickness) const
	{
		SIV3D_ENGINE(Font)->setBufferThickness(m_handle->id(), thickness);
	}

	int32 Font::getBufferThickness() const
	{
		return SIV3D_ENGINE(Font)->getBufferThickness(m_handle->id());
	}

	bool Font::hasGlyph(const char32 ch) const
	{
		return SIV3D_ENGINE(Font)->hasGlyph(m_handle->id(), StringView(&ch, 1));
	}

	bool Font::hasGlyph(const StringView ch) const
	{
		return SIV3D_ENGINE(Font)->hasGlyph(m_handle->id(), ch);
	}

	GlyphIndex Font::getGlyphIndex(const char32 ch) const
	{
		return SIV3D_ENGINE(Font)->getGlyphIndex(m_handle->id(), StringView(&ch, 1));
	}

	GlyphIndex Font::getGlyphIndex(const StringView ch) const
	{
		return SIV3D_ENGINE(Font)->getGlyphIndex(m_handle->id(), ch);
	}

	Array<GlyphCluster> Font::getGlyphClusters(const StringView s) const
	{
		return SIV3D_ENGINE(Font)->getGlyphClusters(m_handle->id(), s);
	}

	GlyphInfo Font::getGlyphInfo(const char32 ch) const
	{
		return SIV3D_ENGINE(Font)->getGlyphInfo(m_handle->id(), StringView(&ch, 1));
	}

	GlyphInfo Font::getGlyphInfo(const StringView ch) const
	{
		return SIV3D_ENGINE(Font)->getGlyphInfo(m_handle->id(), ch);
	}

	OutlineGlyph Font::renderOutline(const char32 ch, const CloseRing closeRing) const
	{
		return SIV3D_ENGINE(Font)->renderOutline(m_handle->id(), StringView(&ch, 1), closeRing);
	}

	OutlineGlyph Font::renderOutline(const StringView ch, const CloseRing closeRing) const
	{
		return SIV3D_ENGINE(Font)->renderOutline(m_handle->id(), ch, closeRing);
	}

	OutlineGlyph Font::renderOutlineByGlyphIndex(const GlyphIndex glyphIndex, const CloseRing closeRing) const
	{
		return SIV3D_ENGINE(Font)->renderOutlineByGlyphIndex(m_handle->id(), glyphIndex, closeRing);
	}

	Array<OutlineGlyph> Font::renderOutlines(const StringView s, const CloseRing closeRing) const
	{
		return SIV3D_ENGINE(Font)->renderOutlines(m_handle->id(), s, closeRing);
	}

	BitmapGlyph Font::renderBitmap(const char32 ch) const
	{
		return SIV3D_ENGINE(Font)->renderBitmap(m_handle->id(), StringView(&ch, 1));
	}

	BitmapGlyph Font::renderBitmap(const StringView ch) const
	{
		return SIV3D_ENGINE(Font)->renderBitmap(m_handle->id(), ch);
	}

	BitmapGlyph Font::renderBitmapByGlyphIndex(const GlyphIndex glyphIndex) const
	{
		return SIV3D_ENGINE(Font)->renderBitmapByGlyphIndex(m_handle->id(), glyphIndex);
	}

	SDFGlyph Font::renderSDF(const char32 ch, const int32 buffer) const
	{
		return SIV3D_ENGINE(Font)->renderSDF(m_handle->id(), StringView(&ch, 1), buffer);
	}

	SDFGlyph Font::renderSDF(const StringView ch, const int32 buffer) const
	{
		return SIV3D_ENGINE(Font)->renderSDF(m_handle->id(), ch, buffer);
	}

	SDFGlyph Font::renderSDFByGlyphIndex(const GlyphIndex glyphIndex, const int32 buffer) const
	{
		return SIV3D_ENGINE(Font)->renderSDFByGlyphIndex(m_handle->id(), glyphIndex, buffer);
	}

	MSDFGlyph Font::renderMSDF(const char32 ch, const int32 buffer) const
	{
		return SIV3D_ENGINE(Font)->renderMSDF(m_handle->id(), StringView(&ch, 1), buffer);
	}

	MSDFGlyph Font::renderMSDF(const StringView ch, const int32 buffer) const
	{
		return SIV3D_ENGINE(Font)->renderMSDF(m_handle->id(), ch, buffer);
	}

	MSDFGlyph Font::renderMSDFByGlyphIndex(const GlyphIndex glyphIndex, const int32 buffer) const
	{
		return SIV3D_ENGINE(Font)->renderMSDFByGlyphIndex(m_handle->id(), glyphIndex, buffer);
	}

	bool Font::preload(const StringView chars) const
	{
		return SIV3D_ENGINE(Font)->preload(m_handle->id(), chars);
	}

	const Texture& Font::getTexture() const
	{
		return SIV3D_ENGINE(Font)->getTexture(m_handle->id());
	}
}
