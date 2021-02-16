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

# include <Siv3D/DrawableText.hpp>
# include <Siv3D/Font/IFont.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	DrawableText::DrawableText(const Font& _font, const String& _text)
		: font{ _font }
		, text{ _text }
		, cluster{ font.getGlyphClusters(text) } {}

	DrawableText::DrawableText(const Font& _font, String&& _text)
		: font{ _font }
		, text{ std::move(_text) }
		, cluster{ font.getGlyphClusters(text) } {}

	Array<double> DrawableText::getXAdvances() const
	{
		return SIV3D_ENGINE(Font)->getXAdvances(font.id(), text, cluster);
	}

	RectF DrawableText::region(const double x, const double y) const
	{
		return region(font.fontSize(), Vec2{ x, y });
	}

	RectF DrawableText::region(const Vec2 pos) const
	{
		return region(font.fontSize(), pos);
	}

	RectF DrawableText::region(const double size, const double x, const double y) const
	{
		return region(size, Vec2{ x, y });
	}

	RectF DrawableText::region(const double size, const Vec2 pos) const
	{
		return SIV3D_ENGINE(Font)->region(font.id(), text, cluster, pos, size, 1.0);
	}

	RectF DrawableText::regionBase(const double x, const double y) const
	{
		return regionBase(font.fontSize(), Vec2{ x, y });
	}

	RectF DrawableText::regionBase(const Vec2 pos) const
	{
		return regionBase(font.fontSize(), pos);
	}

	RectF DrawableText::regionBase(const double size, const double x, const double y) const
	{
		return regionBase(size, Vec2{ x, y });
	}

	RectF DrawableText::regionBase(const double size, const Vec2 pos) const
	{
		return SIV3D_ENGINE(Font)->regionBase(font.id(), text, cluster, pos, size, 1.0);
	}

	RectF DrawableText::regionAt(const double x, const double y) const
	{
		return regionAt(font.fontSize(), Vec2{ x, y });
	}

	RectF DrawableText::regionAt(const Vec2 pos) const
	{
		return regionAt(font.fontSize(), pos);
	}

	RectF DrawableText::regionAt(const double size, const double x, const double y) const
	{
		return regionAt(size, Vec2{ x, y });
	}

	RectF DrawableText::regionAt(const double size, const Vec2 pos) const
	{
		const RectF rect = region(size, Vec2{ 0, 0 });

		return rect.movedBy(pos - rect.center());
	}

	RectF DrawableText::regionBaseAt(const double x, const double y) const
	{
		return regionBaseAt(font.fontSize(), Vec2{ x, y });
	}

	RectF DrawableText::regionBaseAt(const Vec2 pos) const
	{
		return regionBaseAt(font.fontSize(), pos);
	}

	RectF DrawableText::regionBaseAt(const double size, const double x, const double y) const
	{
		return regionBaseAt(size, Vec2{ x, y });
	}

	RectF DrawableText::regionBaseAt(const double size, const Vec2 pos) const
	{
		const RectF rect = regionBase(size, Vec2{ 0, 0 });

		const double drawPosX = (pos.x - (rect.w * 0.5));

		return rect.movedBy(pos.x - (rect.w * 0.5), pos.y);
	}

	RectF DrawableText::draw(const double x, const double y, const ColorF& color) const
	{
		return draw(TextStyle::Default, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::draw(const Vec2& pos, const ColorF& color) const
	{
		return draw(TextStyle::Default, font.fontSize(), pos, color);
	}

	bool DrawableText::draw(const RectF& area, const ColorF& color) const
	{
		return draw(TextStyle::Default, font.fontSize(), area, color);
	}

	RectF DrawableText::draw(const double size, const double x, const double y, const ColorF& color) const
	{
		return draw(TextStyle::Default, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::draw(const double size, const Vec2& pos, const ColorF& color) const
	{
		return draw(TextStyle::Default, size, pos, color);
	}

	bool DrawableText::draw(const double size, const RectF& area, const ColorF& color) const
	{
		return draw(TextStyle::Default, size, area, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double x, const double y, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Vec2& pos, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), pos, color);
	}

	bool DrawableText::draw(const TextStyle& textStyle, const RectF& area, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), area, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const double x, const double y, const ColorF& color) const
	{
		return draw(textStyle, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Vec2& pos, const ColorF& color) const
	{
		return SIV3D_ENGINE(Font)->draw(font.id(), text, cluster, pos, size, textStyle, color, 1.0);
	}

	bool DrawableText::draw(const TextStyle& textStyle, const double size, const RectF& area, const ColorF& color) const
	{
		return SIV3D_ENGINE(Font)->draw(font.id(), text, cluster, area, size, textStyle, color, 1.0);
	}

	RectF DrawableText::drawBase(const double x, const double y, const ColorF& color) const
	{
		return drawBase(TextStyle::Default, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBase(const Vec2& pos, const ColorF& color) const
	{
		return drawBase(TextStyle::Default, font.fontSize(), pos, color);
	}

	RectF DrawableText::drawBase(const double size, const double x, const double y, const ColorF& color) const
	{
		return drawBase(TextStyle::Default, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBase(const double size, const Vec2& pos, const ColorF& color) const
	{
		return drawBase(TextStyle::Default, size, pos, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const double x, const double y, const ColorF& color) const
	{
		return drawBase(textStyle, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const Vec2& pos, const ColorF& color) const
	{
		return drawBase(textStyle, font.fontSize(), pos, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const double size, const double x, const double y, const ColorF& color) const
	{
		return drawBase(textStyle, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const double size, const Vec2& pos, const ColorF& color) const
	{
		return SIV3D_ENGINE(Font)->drawBase(font.id(), text, cluster, pos, size, textStyle, color, 1.0);
	}

	RectF DrawableText::drawAt(const double x, const double y, const ColorF& color) const
	{
		return drawAt(TextStyle::Default, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawAt(const Vec2& pos, const ColorF& color) const
	{
		return drawAt(TextStyle::Default, font.fontSize(), pos, color);
	}

	RectF DrawableText::drawAt(const double size, const double x, const double y, const ColorF& color) const
	{
		return drawAt(TextStyle::Default, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawAt(const double size, const Vec2& pos, const ColorF& color) const
	{
		return drawAt(TextStyle::Default, size, pos, color);
	}

	RectF DrawableText::drawAt(const TextStyle& textStyle, const double x, const double y, const ColorF& color) const
	{
		return drawAt(textStyle, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawAt(const TextStyle& textStyle, const Vec2& pos, const ColorF& color) const
	{
		return drawAt(textStyle, font.fontSize(), pos, color);
	}

	RectF DrawableText::drawAt(const TextStyle& textStyle, const double size, const double x, const double y, const ColorF& color) const
	{
		return drawAt(textStyle, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawAt(const TextStyle& textStyle, const double size, const Vec2& pos, const ColorF& color) const
	{
		const RectF rect = region(size, Vec2{ 0, 0 });

		const Vec2 drawPos = (pos - rect.center());

		return draw(textStyle, size, drawPos, color);
	}

	RectF DrawableText::drawBaseAt(const double x, const double y, const ColorF& color) const
	{
		return drawBaseAt(TextStyle::Default, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBaseAt(const Vec2& pos, const ColorF& color) const
	{
		return drawBaseAt(TextStyle::Default, font.fontSize(), pos, color);
	}

	RectF DrawableText::drawBaseAt(const double size, const double x, const double y, const ColorF& color) const
	{
		return drawBaseAt(TextStyle::Default, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBaseAt(const double size, const Vec2& pos, const ColorF& color) const
	{
		return drawBaseAt(TextStyle::Default, size, pos, color);
	}

	RectF DrawableText::drawBaseAt(const TextStyle& textStyle, const double x, const double y, const ColorF& color) const
	{
		return drawBaseAt(textStyle, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBaseAt(const TextStyle& textStyle, const Vec2& pos, const ColorF& color) const
	{
		return drawBaseAt(textStyle, font.fontSize(), pos, color);
	}

	RectF DrawableText::drawBaseAt(const TextStyle& textStyle, const double size, const double x, const double y, const ColorF& color) const
	{
		return drawBaseAt(textStyle, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBaseAt(const TextStyle& textStyle, const double size, const Vec2& pos, const ColorF& color) const
	{
		const RectF rect = regionBase(size, Vec2{ 0, 0 });

		const double drawPosX = (pos.x - (rect.w * 0.5));

		return drawBase(textStyle, size, Vec2{ drawPosX, pos.y }, color);
	}
}
