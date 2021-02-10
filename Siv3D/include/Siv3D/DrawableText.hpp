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

# pragma once
# include "Common.hpp"
# include "String.hpp"
# include "Font.hpp"
# include "Format.hpp"

namespace s3d
{
	struct DrawableText
	{
		Font font;

		String text;

		DrawableText() = default;

		DrawableText(const Font& _font, const String& _text);

		DrawableText(const Font& _font, String&& _text);

		RectF draw(double x, double y, const ColorF& color = Palette::White) const;

		RectF draw(const Vec2& pos = Vec2{ 0, 0 }, const ColorF& color = Palette::White) const;

		RectF draw(double size, double x, double y, const ColorF& color = Palette::White) const;

		RectF draw(double size, const Vec2& pos, const ColorF& color = Palette::White) const;
	};

	template <class ... Args>
	inline DrawableText Font::operator()(const Args& ... args) const
	{
		return DrawableText(*this, Format(args...));
	}
}
