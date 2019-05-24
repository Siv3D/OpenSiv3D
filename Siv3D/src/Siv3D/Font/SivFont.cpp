//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3DEngine.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/EngineMessageBox.hpp>
# include <AssetHandleManager/AssetReport.hpp>
# include "IFont.hpp"

namespace s3d
{
	template <>
	AssetHandle<Font::Tag>::AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`Font` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<Font::Tag>::AssetHandle(const IDWrapperType id) noexcept
		: m_id(id)
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`Font` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<Font::Tag>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::Get<ISiv3DFont>())
		{
			p->release(m_id);
		}
	}

	Font::Font()
		: m_handle(std::make_shared<FontHandle>())
	{

	}

	Font::Font(const int32 fontSize, const Typeface typeface, const FontStyle style)
		: m_handle(std::make_shared<FontHandle>(Siv3DEngine::Get<ISiv3DFont>()->create(typeface, fontSize, style)))
	{
		ReportAssetCreation();
	}

	Font::Font(const int32 fontSize, const FilePath& path, const FontStyle style)
		: m_handle(std::make_shared<FontHandle>(Siv3DEngine::Get<ISiv3DFont>()->create(path, fontSize, style)))
	{
		ReportAssetCreation();
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

	Font::operator bool() const
	{
		return !isEmpty();
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
		return Siv3DEngine::Get<ISiv3DFont>()->getFamilyName(m_handle->id());
	}

	const String& Font::styleName() const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->getStyleName(m_handle->id());
	}

	int32 Font::fontSize() const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->getFontSize(m_handle->id());
	}

	int32 Font::ascent() const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->getAscent(m_handle->id());
	}

	int32 Font::descent() const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->getDescent(m_handle->id());
	}

	int32 Font::height() const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->getAscent(m_handle->id()) + Siv3DEngine::Get<ISiv3DFont>()->getDescent(m_handle->id());
	}

	Glyph Font::getGlyph(const char32 codePoint) const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->getGlyphs(m_handle->id(), String(1, codePoint))[0];
	}

	Array<Glyph> Font::getGlyphs(const String& text) const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->getGlyphs(m_handle->id(), text);
	}

	Array<Glyph> Font::getVerticalGlyphs(const String& text) const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->getVerticalGlyphs(m_handle->id(), text);
	}

	OutlineGlyph Font::getOutlineGlyph(const char32 codePoint) const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->getOutlineGlyph(m_handle->id(), codePoint);
	}

	DrawableText Font::operator()(const String& text) const
	{
		return{ *this, text };
	}

	DrawableText Font::operator()(String&& text) const
	{
		return{ *this, std::move(text) };
	}

	const Texture& Font::getTexture() const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->getTexture(m_handle->id());
	}


	GlyphIterator::GlyphIterator(const Font& font, String::const_iterator it, int32 index)
		: m_font(font)
		, m_iterator(it)
		, m_index(index)
	{
	
	}

	GlyphIterator& GlyphIterator::operator ++()
	{
		++m_iterator;

		++m_index;

		return *this;
	}

	Glyph GlyphIterator::operator *() const
	{
		Glyph glyph = m_font.getGlyph(*m_iterator);

		glyph.index = m_index;

		return glyph;
	}

	bool GlyphIterator::operator ==(const GlyphIterator& other) const
	{
		return m_iterator == other.m_iterator;
	}

	bool GlyphIterator::operator !=(const GlyphIterator& other) const
	{
		return m_iterator != other.m_iterator;
	}



	DrawableText::DrawableText(const Font& _font, const String& _text)
		: font(_font)
		, text(_text)
	{
	
	}

	DrawableText::DrawableText(const Font& _font, String&& _text)
		: font(_font)
		, text(std::move(_text))
	{
	
	}

	GlyphIterator DrawableText::begin() const
	{
		return GlyphIterator(font, text.begin(), 0);
	}

	GlyphIterator DrawableText::end() const
	{
		return GlyphIterator(font, text.end(), static_cast<int32>(text.size()));
	}

	RectF DrawableText::boundingRect(const double x, const double y) const
	{
		return boundingRect(Vec2(x, y));
	}

	RectF DrawableText::boundingRect(const Vec2& pos) const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->getBoundingRect(font.id(), text, 1.0).moveBy(pos);
	}

	RectF DrawableText::boundingRect(Arg::topLeft_<Vec2> topLeft) const
	{
		return boundingRect(*topLeft);
	}

	RectF DrawableText::boundingRect(Arg::topRight_<Vec2> topRight) const
	{
		return boundingRect(topRight->movedBy(-region().w, 0));
	}

	RectF DrawableText::boundingRect(Arg::bottomLeft_<Vec2> bottomLeft) const
	{
		return boundingRect(bottomLeft->movedBy(0, -region().h));
	}

	RectF DrawableText::boundingRect(Arg::bottomRight_<Vec2> bottomRight) const
	{
		return boundingRect(bottomRight->movedBy(-region().size));
	}

	RectF DrawableText::boundingRect(Arg::topCenter_<Vec2> topCenter) const
	{
		return boundingRect(topCenter->movedBy(-region().w * 0.5, 0));
	}

	RectF DrawableText::boundingRect(Arg::bottomCenter_<Vec2> bottomCenter) const
	{
		return boundingRect(bottomCenter->movedBy(-region().w * 0.5, -region().h));
	}

	RectF DrawableText::boundingRect(Arg::leftCenter_<Vec2> leftCenter) const
	{
		return boundingRect(leftCenter->movedBy(0, -region().h * 0.5));
	}

	RectF DrawableText::boundingRect(Arg::rightCenter_<Vec2> rightCenter) const
	{
		return boundingRect(rightCenter->movedBy(-region().w, -region().h * 0.5));
	}

	RectF DrawableText::boundingRect(Arg::center_<Vec2> center) const
	{
		return boundingRectAt(*center);
	}

	RectF DrawableText::boundingRectAt(const double x, const double y) const
	{
		return boundingRectAt(Vec2(x, y));
	}

	RectF DrawableText::boundingRectAt(const Vec2 & pos) const
	{
		const RectF rect = boundingRect();

		return rect.movedBy(pos - rect.center());
	}

	RectF DrawableText::region(const double x, const double y) const
	{
		return region(Vec2(x, y));
	}

	Rect DrawableText::region(const Point& pos) const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->getRegion(font.id(), text, 1.0).moveBy(pos);
	}

	RectF DrawableText::region(const Vec2& pos) const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->getRegion(font.id(), text, 1.0).moveBy(pos);
	}

	RectF DrawableText::region(Arg::topLeft_<Vec2> topLeft) const
	{
		return region(*topLeft);
	}

	RectF DrawableText::region(Arg::topRight_<Vec2> topRight) const
	{
		return region(topRight->movedBy(-region().w, 0));
	}

	RectF DrawableText::region(Arg::bottomLeft_<Vec2> bottomLeft) const
	{
		return region(bottomLeft->movedBy(0, -region().h));
	}

	RectF DrawableText::region(Arg::bottomRight_<Vec2> bottomRight) const
	{
		return region(bottomRight->movedBy(-region().size));
	}

	RectF DrawableText::region(Arg::topCenter_<Vec2> topCenter) const
	{
		return region(topCenter->movedBy(-region().w * 0.5, 0));
	}

	RectF DrawableText::region(Arg::bottomCenter_<Vec2> bottomCenter) const
	{
		return region(bottomCenter->movedBy(-region().w * 0.5, -region().h));
	}

	RectF DrawableText::region(Arg::leftCenter_<Vec2> leftCenter) const
	{
		return region(leftCenter->movedBy(0, -region().h * 0.5));
	}

	RectF DrawableText::region(Arg::rightCenter_<Vec2> rightCenter) const
	{
		return region(rightCenter->movedBy(-region().w, -region().h * 0.5));
	}

	RectF DrawableText::region(Arg::center_<Vec2> center) const
	{
		return regionAt(*center);
	}

	RectF DrawableText::regionAt(const double x, const double y) const
	{
		return regionAt(Vec2(x, y));
	}

	RectF DrawableText::regionAt(const Vec2 & pos) const
	{
		const RectF rect = region();

		return rect.movedBy(pos - rect.center());
	}

	Array<int32> DrawableText::getXAdvances() const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->getXAdvances(font.id(), text);
	}

	RectF DrawableText::draw(const double x, const double y, const ColorF& color) const
	{
		return draw(Vec2(x, y), color);
	}

	RectF DrawableText::draw(const Vec2& pos, const ColorF& color) const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->draw(font.id(), text, pos, color, 1.0);
	}

	RectF DrawableText::draw(Arg::topLeft_<Vec2> topLeft, const ColorF& color) const
	{
		return draw(*topLeft, color);
	}

	RectF DrawableText::draw(Arg::topRight_<Vec2> topRight, const ColorF& color) const
	{
		return draw(topRight->movedBy(-region().w, 0), color);
	}

	RectF DrawableText::draw(Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color) const
	{
		return draw(bottomLeft->movedBy(0, -region().h), color);
	}

	RectF DrawableText::draw(Arg::bottomRight_<Vec2> bottomRight, const ColorF & color) const
	{
		return draw(bottomRight->movedBy(-region().size), color);
	}

	RectF DrawableText::draw(Arg::topCenter_<Vec2> topCenter, const ColorF & color) const
	{
		return draw(topCenter->movedBy(-region().w * 0.5, 0), color);
	}

	RectF DrawableText::draw(Arg::bottomCenter_<Vec2> bottomCenter, const ColorF & color) const
	{
		return draw(bottomCenter->movedBy(-region().w * 0.5, -region().h), color);
	}

	RectF DrawableText::draw(Arg::leftCenter_<Vec2> leftCenter, const ColorF & color) const
	{
		return draw(leftCenter->movedBy(0, -region().h * 0.5), color);
	}

	RectF DrawableText::draw(Arg::rightCenter_<Vec2> rightCenter, const ColorF & color) const
	{
		return draw(rightCenter->movedBy(-region().w, -region().h * 0.5), color);
	}

	RectF DrawableText::draw(Arg::center_<Vec2> center, const ColorF & color) const
	{
		return drawAt(*center, color);
	}

	RectF DrawableText::drawAt(const double x, const double y, const ColorF & color) const
	{
		return drawAt(Vec2(x, y), color);
	}

	RectF DrawableText::drawAt(const Vec2& pos, const ColorF & color) const
	{
		return draw(pos - region().center(), color);
	}

	RectF DrawableText::drawBase(const double x, const double y, const ColorF & color) const
	{
		return drawBase(Vec2(x, y), color);
	}

	RectF DrawableText::drawBase(const Vec2& pos, const ColorF & color) const
	{
		return draw(pos.movedBy(0, -font.ascent()), color);
	}

	RectF DrawableText::drawBase(Arg::left_<Vec2> left, const ColorF & color) const
	{
		return drawBase(*left, color);
	}

	RectF DrawableText::drawBase(Arg::right_<Vec2> right, const ColorF & color) const
	{
		return drawBase(right->movedBy(-region().w, 0), color);
	}

	RectF DrawableText::drawBase(Arg::center_<Vec2> center, const ColorF & color) const
	{
		return drawBase(center->movedBy(-region().w * 0.5, 0), color);
	}

	RectF DrawableText::drawBaseAt(const double x, const double y, const ColorF & color) const
	{
		return drawBaseAt(Vec2(x, y), color);
	}

	RectF DrawableText::drawBaseAt(const Vec2& pos, const ColorF & color) const
	{
		return drawBase(pos - region().center(), color);
	}

	bool DrawableText::draw(const RectF& area, const ColorF& color) const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->draw(font.id(), text, area, color, 1.0);
	}

	Rect DrawableText::paint(Image& dst, const int32 x, const int32 y, const Color& color) const
	{
		return paint(dst, Point(x, y), color);
	}

	Rect DrawableText::paint(Image& dst, const Point& pos, const Color& color) const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->paint(font.id(), dst, text, pos, color, 1.0);
	}

	RectF DrawableText::paintAt(Image& dst, const int32 x, const int32 y, const Color& color) const
	{
		return paintAt(dst, Point(x, y), color);
	}

	RectF DrawableText::paintAt(Image& dst, const Point& pos, const Color& color) const
	{
		return paint(dst, (pos - region().center()).asPoint(), color);
	}

	Rect DrawableText::overwrite(Image & dst, const int32 x, const int32 y, const Color& color) const
	{
		return overwrite(dst, Point(x, y), color);
	}

	Rect DrawableText::overwrite(Image& dst, const Point& pos, const Color& color) const
	{
		return Siv3DEngine::Get<ISiv3DFont>()->overwrite(font.id(), dst, text, pos, color, 1.0);
	}

	RectF DrawableText::overwriteAt(Image& dst, const int32 x, const int32 y, const Color& color) const
	{
		return overwriteAt(dst, Point(x, y), color);
	}

	RectF DrawableText::overwriteAt(Image& dst, const Point& pos, const Color& color) const
	{
		return overwrite(dst, (pos - region().center()).asPoint(), color);
	}
}
