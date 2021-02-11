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
		, text{ _text } {}

	DrawableText::DrawableText(const Font& _font, String&& _text)
		: font{ _font }
		, text{ std::move(_text) } {}

	RectF DrawableText::draw(const double x, const double y, const ColorF& color) const
	{
		return draw(font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::draw(const Vec2& pos, const ColorF& color) const
	{
		return draw(font.fontSize(), pos, color);
	}

	RectF DrawableText::draw(const double size, const double x, const double y, const ColorF& color) const
	{
		return draw(size, Vec2{ x, y }, color);
	}

	RectF DrawableText::draw(const double size, const Vec2& pos, const ColorF& color) const
	{
		return SIV3D_ENGINE(Font)->draw(font.id(), text, pos, size, color, 1.0);
	}

	RectF DrawableText::drawBase(const double x, const double y, const ColorF& color) const
	{
		return drawBase(font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBase(const Vec2& pos, const ColorF& color) const
	{
		return drawBase(font.fontSize(), pos, color);
	}

	RectF DrawableText::drawBase(const double size, const double x, const double y, const ColorF& color) const
	{
		return drawBase(size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBase(const double size, const Vec2& pos, const ColorF& color) const
	{
		return SIV3D_ENGINE(Font)->drawBase(font.id(), text, pos, size, color, 1.0);
	}
}
