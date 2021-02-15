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
# include "TextStyle.hpp"

namespace s3d
{
	struct DrawableText
	{
		Font font;

		String text;

		Array<GlyphCluster> cluster;

		DrawableText() = default;

		DrawableText(const Font& _font, const String& _text);

		DrawableText(const Font& _font, String&& _text);

		[[nodiscard]]
		RectF region(double x, double y) const;

		[[nodiscard]]
		RectF region(Vec2 pos = Vec2{ 0, 0 }) const;

		[[nodiscard]]
		RectF region(double size, double x, double y) const;

		[[nodiscard]]
		RectF region(double size, Vec2 pos = Vec2{ 0, 0 }) const;

		[[nodiscard]]
		RectF regionBase(double x, double y) const;

		[[nodiscard]]
		RectF regionBase(Vec2 pos = Vec2{ 0, 0 }) const;

		[[nodiscard]]
		RectF regionBase(double size, double x, double y) const;

		[[nodiscard]]
		RectF regionBase(double size, Vec2 pos = Vec2{ 0, 0 }) const;

		[[nodiscard]]
		RectF regionAt(double x, double y) const;

		[[nodiscard]]
		RectF regionAt(Vec2 pos = Vec2{ 0, 0 }) const;

		[[nodiscard]]
		RectF regionAt(double size, double x, double y) const;

		[[nodiscard]]
		RectF regionAt(double size, Vec2 pos = Vec2{ 0, 0 }) const;

		[[nodiscard]]
		RectF regionBaseAt(double x, double y) const;

		[[nodiscard]]
		RectF regionBaseAt(Vec2 pos = Vec2{ 0, 0 }) const;

		[[nodiscard]]
		RectF regionBaseAt(double size, double x, double y) const;

		[[nodiscard]]
		RectF regionBaseAt(double size, Vec2 pos = Vec2{ 0, 0 }) const;

		RectF draw(double x, double y, const ColorF& color = Palette::White) const;

		RectF draw(const Vec2& pos = Vec2{ 0, 0 }, const ColorF& color = Palette::White) const;

		RectF draw(double size, double x, double y, const ColorF& color = Palette::White) const;

		RectF draw(double size, const Vec2& pos, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, double x, double y, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, const Vec2& pos = Vec2{ 0, 0 }, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, double size, double x, double y, const ColorF& color = Palette::White) const;

		RectF draw(const TextStyle& textStyle, double size, const Vec2& pos, const ColorF& color = Palette::White) const;

		RectF drawBase(double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBase(const Vec2& pos = Vec2{ 0, 0 }, const ColorF& color = Palette::White) const;

		RectF drawBase(double size, double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBase(double size, const Vec2& pos, const ColorF& color = Palette::White) const;

		RectF drawBase(const TextStyle& textStyle, double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBase(const TextStyle& textStyle, const Vec2& pos = Vec2{ 0, 0 }, const ColorF& color = Palette::White) const;

		RectF drawBase(const TextStyle& textStyle, double size, double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBase(const TextStyle& textStyle, double size, const Vec2& pos, const ColorF& color = Palette::White) const;

		RectF drawAt(double x, double y, const ColorF& color = Palette::White) const;

		RectF drawAt(const Vec2& pos = Vec2{ 0, 0 }, const ColorF& color = Palette::White) const;

		RectF drawAt(double size, double x, double y, const ColorF& color = Palette::White) const;

		RectF drawAt(double size, const Vec2& pos, const ColorF& color = Palette::White) const;

		RectF drawAt(const TextStyle & textStyle, double x, double y, const ColorF & color = Palette::White) const;

		RectF drawAt(const TextStyle & textStyle, const Vec2 & pos = Vec2{ 0, 0 }, const ColorF & color = Palette::White) const;

		RectF drawAt(const TextStyle & textStyle, double size, double x, double y, const ColorF & color = Palette::White) const;

		RectF drawAt(const TextStyle & textStyle, double size, const Vec2 & pos, const ColorF & color = Palette::White) const;

		RectF drawBaseAt(double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBaseAt(const Vec2& pos = Vec2{ 0, 0 }, const ColorF& color = Palette::White) const;

		RectF drawBaseAt(double size, double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBaseAt(double size, const Vec2& pos, const ColorF& color = Palette::White) const;
		
		RectF drawBaseAt(const TextStyle& textStyle, double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBaseAt(const TextStyle& textStyle, const Vec2& pos = Vec2{ 0, 0 }, const ColorF& color = Palette::White) const;

		RectF drawBaseAt(const TextStyle& textStyle, double size, double x, double y, const ColorF& color = Palette::White) const;

		RectF drawBaseAt(const TextStyle& textStyle, double size, const Vec2& pos, const ColorF& color = Palette::White) const;
	};

	template <class ... Args>
	inline DrawableText Font::operator()(const Args& ... args) const
	{
		return DrawableText(*this, Format(args...));
	}
}
