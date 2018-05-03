//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../Siv3DEngine.hpp"
# include "IFont.hpp"
# include <Siv3D/Font.hpp>
# include "../Profiler/IProfiler.hpp"

namespace s3d
{
	template <>
	AssetHandle<Font::Handle>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::GetFont())
		{
			p->release(m_id);
		}
	}

	Font::Font()
		: m_handle(std::make_shared<FontHandle>())
	{

	}

	Font::Font(const int32 fontSize, const Typeface typeface, const FontStyle style)
		: m_handle(std::make_shared<FontHandle>(Siv3DEngine::GetFont()->create(typeface, fontSize, style)))
	{
		ASSET_CREATION();
	}

	Font::Font(const int32 fontSize, const FilePath& path, const FontStyle style)
		: m_handle(std::make_shared<FontHandle>(Siv3DEngine::GetFont()->create(path, fontSize, style)))
	{
		ASSET_CREATION();
	}

	Font::~Font()
	{

	}

	void Font::release()
	{
		m_handle = std::make_shared<FontHandle>();
	}

	bool Font::isEmpty() const
	{
		return m_handle->id().isNullAsset();
	}

	FontID Font::id() const
	{
		return m_handle->id();
	}

	bool Font::operator ==(const Font& font) const
	{
		return m_handle->id() == font.m_handle->id();
	}

	bool Font::operator !=(const Font& font) const
	{
		return m_handle->id() != font.m_handle->id();
	}

	const String& Font::familyName() const
	{
		return Siv3DEngine::GetFont()->getFamilyName(m_handle->id());
	}

	const String& Font::styleName() const
	{
		return Siv3DEngine::GetFont()->getStyleName(m_handle->id());
	}

	int32 Font::fontSize() const
	{
		return Siv3DEngine::GetFont()->getFontSize(m_handle->id());
	}

	int32 Font::ascent() const
	{
		return Siv3DEngine::GetFont()->getAscent(m_handle->id());
	}

	int32 Font::descent() const
	{
		return Siv3DEngine::GetFont()->getDescent(m_handle->id());
	}

	int32 Font::height() const
	{
		return Siv3DEngine::GetFont()->getAscent(m_handle->id()) + Siv3DEngine::GetFont()->getDescent(m_handle->id());
	}

	Glyph Font::getGlyph(const char32 codePoint) const
	{
		return Siv3DEngine::GetFont()->getGlyphs(m_handle->id(), String(1, codePoint))[0];
	}

	Array<Glyph> Font::getGlyphs(const String& text) const
	{
		return Siv3DEngine::GetFont()->getGlyphs(m_handle->id(), text);
	}

	Array<Glyph> Font::getVerticalGlyphs(const String& text) const
	{
		return Siv3DEngine::GetFont()->getVerticalGlyphs(m_handle->id(), text);
	}

	OutlineGlyph Font::getOutlineGlyph(const char32 codePoint) const
	{
		return Siv3DEngine::GetFont()->getOutlineGlyph(m_handle->id(), codePoint);
	}

	RectF DrawableText::boundingRect(const Vec2& pos) const
	{
		return Siv3DEngine::GetFont()->getBoundingRect(font.id(), codePoints, 1.0).moveBy(pos);
	}

	Rect DrawableText::region(const Point& pos) const
	{
		return Siv3DEngine::GetFont()->getRegion(font.id(), codePoints, 1.0).moveBy(pos);
	}

	RectF DrawableText::region(const Vec2& pos) const
	{
		return Siv3DEngine::GetFont()->getRegion(font.id(), codePoints, 1.0).moveBy(pos);
	}

	Array<int32> DrawableText::getXAdvances() const
	{
		return Siv3DEngine::GetFont()->getXAdvances(font.id(), codePoints);
	}

	RectF DrawableText::draw(const Vec2& pos, const ColorF& color) const
	{
		return Siv3DEngine::GetFont()->draw(font.id(), codePoints, pos, color, 1.0);
	}

	bool DrawableText::draw(const RectF& area, const ColorF& color) const
	{
		return Siv3DEngine::GetFont()->draw(font.id(), codePoints, area, color, 1.0);
	}

	Rect DrawableText::paint(Image& dst, const Point& pos, const Color& color) const
	{
		return Siv3DEngine::GetFont()->paint(font.id(), dst, codePoints, pos, color, 1.0);
	}

	Rect DrawableText::overwrite(Image& dst, const Point& pos, const Color& color) const
	{
		return Siv3DEngine::GetFont()->overwrite(font.id(), dst, codePoints, pos, color, 1.0);
	}
}
