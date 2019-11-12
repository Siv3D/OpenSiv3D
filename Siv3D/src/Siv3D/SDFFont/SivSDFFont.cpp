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
# include <Siv3D/SDFFont.hpp>
# include <Siv3D/EngineMessageBox.hpp>
# include <AssetHandleManager/AssetReport.hpp>
# include "ISDFFont.hpp"

namespace s3d
{
	template <>
	AssetHandle<SDFFont::Tag>::AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`SDFFont` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<SDFFont::Tag>::AssetHandle(const IDWrapperType id) noexcept
		: m_id(id)
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`SDFFont` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<SDFFont::Tag>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::Get<ISiv3DSDFFont>())
		{
			p->release(m_id);
		}
	}

	SDFFont::SDFFont()
		: m_handle(std::make_shared<SDFFontHandle>())
	{

	}

	SDFFont::SDFFont(const int32 baseSize, const Typeface typeface, const FontStyle style)
		: m_handle(std::make_shared<SDFFontHandle>(Siv3DEngine::Get<ISiv3DSDFFont>()->create(typeface, baseSize, style)))
	{
		ReportAssetCreation();
	}

	SDFFont::SDFFont(const int32 baseSize, const FilePath& path, const FontStyle style)
		: m_handle(std::make_shared<SDFFontHandle>(Siv3DEngine::Get<ISiv3DSDFFont>()->create(path, baseSize, style)))
	{
		ReportAssetCreation();
	}

	SDFFont::SDFFont(const std::pair<FilePath, FilePath>& prerenderedFiles, const int32 baseSize, const Typeface typeface, const FontStyle style)
		: m_handle(std::make_shared<SDFFontHandle>(Siv3DEngine::Get<ISiv3DSDFFont>()->create(prerenderedFiles, typeface, baseSize, style)))
	{
		ReportAssetCreation();
	}

	SDFFont::SDFFont(const std::pair<FilePath, FilePath>& prerenderedFiles, const int32 baseSize, const FilePath& path, const FontStyle style)
		: m_handle(std::make_shared<SDFFontHandle>(Siv3DEngine::Get<ISiv3DSDFFont>()->create(prerenderedFiles, path, baseSize, style)))
	{
		ReportAssetCreation();
	}

	SDFFont::~SDFFont()
	{

	}

	void SDFFont::release()
	{
		m_handle = std::make_shared<SDFFontHandle>();
	}

	bool SDFFont::isEmpty() const
	{
		return m_handle->id().isNullAsset();
	}

	SDFFont::operator bool() const
	{
		return !isEmpty();
	}

	SDFFontID SDFFont::id() const
	{
		return m_handle->id();
	}

	bool SDFFont::operator ==(const SDFFont& font) const
	{
		return m_handle->id() == font.m_handle->id();
	}

	bool SDFFont::operator !=(const SDFFont& font) const
	{
		return m_handle->id() != font.m_handle->id();
	}

	const String& SDFFont::familyName() const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getFamilyName(m_handle->id());
	}

	const String& SDFFont::styleName() const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getStyleName(m_handle->id());
	}

	int32 SDFFont::baseSize() const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getBaseSize(m_handle->id());
	}

	double SDFFont::ascent() const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getAscent(m_handle->id());
	}

	double SDFFont::descent() const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getDescent(m_handle->id());
	}

	double SDFFont::height() const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getHeight(m_handle->id());
	}

	double SDFFont::pixelRange() const
	{
		// [Siv3D ToDo]
		return baseSize() / 8.0;
	}

	const SDFFont& SDFFont::preload(const StringView text) const
	{
		Siv3DEngine::Get<ISiv3DSDFFont>()->preload(m_handle->id(), text);

		return *this;
	}

	bool SDFFont::saveGlyphs(const FilePathView imagePath, const FilePathView jsonPath) const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->saveGlyphs(m_handle->id(), imagePath, jsonPath);
	}

	GlyphF SDFFont::getGlyph(const char32 codePoint) const
	{
		return getGlyphs(StringView(&codePoint, 1)).front();
	}

	Array<GlyphF> SDFFont::getGlyphs(const StringView text) const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getGlyphs(m_handle->id(), text);
	}

	SDFDrawableText SDFFont::operator()(const String& text) const
	{
		return{ *this, text };
	}

	SDFDrawableText SDFFont::operator()(String&& text) const
	{
		return{ *this, std::move(text) };
	}

	const Texture& SDFFont::getTexture() const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getTexture(m_handle->id());
	}



	GlyphFIterator::GlyphFIterator(const SDFFont& font, String::const_iterator it, int32 index)
		: m_font(font)
		, m_iterator(it)
		, m_index(index)
	{

	}

	GlyphFIterator& GlyphFIterator::operator ++()
	{
		++m_iterator;

		++m_index;

		return *this;
	}

	GlyphF GlyphFIterator::operator *() const
	{
		GlyphF glyph = m_font.getGlyph(*m_iterator);

		glyph.index = m_index;

		return glyph;
	}

	bool GlyphFIterator::operator ==(const GlyphFIterator& other) const
	{
		return m_iterator == other.m_iterator;
	}

	bool GlyphFIterator::operator !=(const GlyphFIterator& other) const
	{
		return m_iterator != other.m_iterator;
	}



	SDFDrawableText::SDFDrawableText(const SDFFont& _font, const String& _text)
		: font(_font)
		, text(_text)
	{

	}

	SDFDrawableText::SDFDrawableText(const SDFFont& _font, String&& _text)
		: font(_font)
		, text(std::move(_text))
	{

	}

	GlyphFIterator SDFDrawableText::begin() const
	{
		return GlyphFIterator(font, text.begin(), 0);
	}

	GlyphFIterator SDFDrawableText::end() const
	{
		return GlyphFIterator(font, text.end(), static_cast<int32>(text.size()));
	}

	RectF SDFDrawableText::boundingRect(const double fontSize, const double x, const double y) const
	{
		return boundingRect(fontSize, Vec2(x, y));
	}

	RectF SDFDrawableText::boundingRect(const double fontSize, const Vec2& pos) const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getBoundingRect(font.id(), fontSize, text, 1.0).moveBy(pos);
	}

	RectF SDFDrawableText::boundingRect(const double fontSize, Arg::topLeft_<Vec2> topLeft) const
	{
		return boundingRect(fontSize, *topLeft);
	}

	RectF SDFDrawableText::boundingRect(const double fontSize, Arg::topRight_<Vec2> topRight) const
	{
		return boundingRect(fontSize, topRight->movedBy(-region(fontSize).w, 0));
	}

	RectF SDFDrawableText::boundingRect(const double fontSize, Arg::bottomLeft_<Vec2> bottomLeft) const
	{
		return boundingRect(fontSize, bottomLeft->movedBy(0, -region(fontSize).h));
	}

	RectF SDFDrawableText::boundingRect(const double fontSize, Arg::bottomRight_<Vec2> bottomRight) const
	{
		return boundingRect(fontSize, bottomRight->movedBy(-region(fontSize).size));
	}

	RectF SDFDrawableText::boundingRect(const double fontSize, Arg::topCenter_<Vec2> topCenter) const
	{
		return boundingRect(fontSize, topCenter->movedBy(-region(fontSize).w * 0.5, 0));
	}

	RectF SDFDrawableText::boundingRect(const double fontSize, Arg::bottomCenter_<Vec2> bottomCenter) const
	{
		return boundingRect(fontSize, bottomCenter->movedBy(-region(fontSize).w * 0.5, -region(fontSize).h));
	}

	RectF SDFDrawableText::boundingRect(const double fontSize, Arg::leftCenter_<Vec2> leftCenter) const
	{
		return boundingRect(fontSize, leftCenter->movedBy(0, -region(fontSize).h * 0.5));
	}

	RectF SDFDrawableText::boundingRect(const double fontSize, Arg::rightCenter_<Vec2> rightCenter) const
	{
		return boundingRect(fontSize, rightCenter->movedBy(-region(fontSize).w, -region(fontSize).h * 0.5));
	}

	RectF SDFDrawableText::boundingRect(const double fontSize, Arg::center_<Vec2> center) const
	{
		return boundingRectAt(fontSize , *center);
	}

	RectF SDFDrawableText::boundingRectAt(const double fontSize, const double x, const double y) const
	{
		return boundingRectAt(fontSize, Vec2(x, y));
	}

	RectF SDFDrawableText::boundingRectAt(const double fontSize, const Vec2& pos) const
	{
		const RectF rect = boundingRect(fontSize);

		return rect.movedBy(pos - rect.center());
	}

	RectF SDFDrawableText::region(const double fontSize, const double x, const double y) const
	{
		return region(fontSize, Vec2(x, y));
	}

	Rect SDFDrawableText::region(const double fontSize, const Point& pos) const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getRegion(font.id(), fontSize, text, 1.0).moveBy(pos);
	}

	RectF SDFDrawableText::region(const double fontSize, const Vec2& pos) const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getRegion(font.id(), fontSize, text, 1.0).moveBy(pos);
	}

	RectF SDFDrawableText::region(const double fontSize, Arg::topLeft_<Vec2> topLeft) const
	{
		return region(fontSize, *topLeft);
	}

	RectF SDFDrawableText::region(const double fontSize, Arg::topRight_<Vec2> topRight) const
	{
		return region(fontSize, topRight->movedBy(-region(fontSize).w, 0));
	}

	RectF SDFDrawableText::region(const double fontSize, Arg::bottomLeft_<Vec2> bottomLeft) const
	{
		return region(fontSize, bottomLeft->movedBy(0, -region(fontSize).h));
	}

	RectF SDFDrawableText::region(const double fontSize, Arg::bottomRight_<Vec2> bottomRight) const
	{
		return region(fontSize, bottomRight->movedBy(-region(fontSize).size));
	}

	RectF SDFDrawableText::region(const double fontSize, Arg::topCenter_<Vec2> topCenter) const
	{
		return region(fontSize, topCenter->movedBy(-region(fontSize).w * 0.5, 0));
	}

	RectF SDFDrawableText::region(const double fontSize, Arg::bottomCenter_<Vec2> bottomCenter) const
	{
		return region(fontSize, bottomCenter->movedBy(-region(fontSize).w * 0.5, -region(fontSize).h));
	}

	RectF SDFDrawableText::region(const double fontSize, Arg::leftCenter_<Vec2> leftCenter) const
	{
		return region(fontSize, leftCenter->movedBy(0, -region(fontSize).h * 0.5));
	}

	RectF SDFDrawableText::region(const double fontSize, Arg::rightCenter_<Vec2> rightCenter) const
	{
		return region(fontSize, rightCenter->movedBy(-region(fontSize).w, -region(fontSize).h * 0.5));
	}

	RectF SDFDrawableText::region(const double fontSize, Arg::center_<Vec2> center) const
	{
		return regionAt(fontSize, *center);
	}

	RectF SDFDrawableText::regionAt(const double fontSize, const double x, const double y) const
	{
		return regionAt(fontSize, Vec2(x, y));
	}

	RectF SDFDrawableText::regionAt(const double fontSize, const Vec2& pos) const
	{
		const RectF rect = region(fontSize);

		return rect.movedBy(pos - rect.center());
	}

	Array<double> SDFDrawableText::getXAdvances(const double fontSize) const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getXAdvances(font.id(), fontSize, text);
	}

	RectF SDFDrawableText::draw(const double fontSize, const double x, const double y, const ColorF& color) const
	{
		return draw(fontSize, Vec2(x, y), color);
	}

	RectF SDFDrawableText::draw(const double fontSize, const Vec2& pos, const ColorF& color) const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->draw(font.id(), fontSize, text, pos, color, 1.0);
	}

	RectF SDFDrawableText::draw(const double fontSize, Arg::topLeft_<Vec2> topLeft, const ColorF& color) const
	{
		return draw(fontSize, *topLeft, color);
	}

	RectF SDFDrawableText::draw(const double fontSize, Arg::topRight_<Vec2> topRight, const ColorF& color) const
	{
		return draw(fontSize, topRight->movedBy(-region(fontSize).w, 0), color);
	}

	RectF SDFDrawableText::draw(const double fontSize, Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color) const
	{
		return draw(fontSize, bottomLeft->movedBy(0, -region(fontSize).h), color);
	}

	RectF SDFDrawableText::draw(const double fontSize, Arg::bottomRight_<Vec2> bottomRight, const ColorF& color) const
	{
		return draw(fontSize, bottomRight->movedBy(-region(fontSize).size), color);
	}

	RectF SDFDrawableText::draw(const double fontSize, Arg::topCenter_<Vec2> topCenter, const ColorF& color) const
	{
		return draw(fontSize, topCenter->movedBy(-region(fontSize).w * 0.5, 0), color);
	}

	RectF SDFDrawableText::draw(const double fontSize, Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color) const
	{
		return draw(fontSize, bottomCenter->movedBy(-region(fontSize).w * 0.5, -region(fontSize).h), color);
	}

	RectF SDFDrawableText::draw(const double fontSize, Arg::leftCenter_<Vec2> leftCenter, const ColorF& color) const
	{
		return draw(fontSize, leftCenter->movedBy(0, -region(fontSize).h * 0.5), color);
	}

	RectF SDFDrawableText::draw(const double fontSize, Arg::rightCenter_<Vec2> rightCenter, const ColorF& color) const
	{
		return draw(fontSize, rightCenter->movedBy(-region(fontSize).w, -region(fontSize).h * 0.5), color);
	}

	RectF SDFDrawableText::draw(const double fontSize, Arg::center_<Vec2> center, const ColorF& color) const
	{
		return drawAt(fontSize , *center, color);
	}

	RectF SDFDrawableText::drawAt(const double fontSize, const double x, const double y, const ColorF& color) const
	{
		return drawAt(fontSize, Vec2(x, y), color);
	}

	RectF SDFDrawableText::drawAt(const double fontSize, const Vec2& pos, const ColorF& color) const
	{
		return draw(fontSize, pos - region(fontSize).center(), color);
	}

	RectF SDFDrawableText::drawBase(const double fontSize, const double x, const double y, const ColorF& color) const
	{
		return drawBase(fontSize, Vec2(x, y), color);
	}

	RectF SDFDrawableText::drawBase(const double fontSize, const Vec2& pos, const ColorF& color) const
	{
		return draw(fontSize, pos.movedBy(0, -font.ascent()), color);
	}

	RectF SDFDrawableText::drawBase(const double fontSize, Arg::left_<Vec2> left, const ColorF& color) const
	{
		return drawBase(fontSize , *left, color);
	}

	RectF SDFDrawableText::drawBase(const double fontSize, Arg::right_<Vec2> right, const ColorF& color) const
	{
		return drawBase(fontSize, right->movedBy(-region(fontSize).w, 0), color);
	}

	RectF SDFDrawableText::drawBase(const double fontSize, Arg::center_<Vec2> center, const ColorF& color) const
	{
		return drawBase(fontSize, center->movedBy(-region(fontSize).w * 0.5, 0), color);
	}

	RectF SDFDrawableText::drawBaseAt(const double fontSize, const double x, const double y, const ColorF& color) const
	{
		return drawBaseAt(fontSize, Vec2(x, y), color);
	}

	RectF SDFDrawableText::drawBaseAt(const double fontSize, const Vec2& pos, const ColorF& color) const
	{
		return drawBase(fontSize, pos - region(fontSize).center(), color);
	}
}
