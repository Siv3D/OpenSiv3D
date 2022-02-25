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

# pragma once

namespace s3d
{
	namespace InputIcon
	{
		inline Vec2 GetSize(const StringView label, const Font& font, const double size)
		{
			const double innerSize = (size * 0.8);
			const double width = (font(label).region().w + size * 0.6);
			return{ (innerSize < width ? width : size), size };
		}

		inline Vec2 GetSize(const Input& input, const Font& font, const double size)
		{
			return GetSize(input.name(), font, size);
		}

		inline void DrawAt(const StringView label, const bool isPressed, const Vec2& center, const Font& font, const double size, const ColorF& keyColor, const ColorF& labelColor)
		{
			const Vec2 outerKeyCenter = center + Vec2::Down(size * 0.1 * 0.5 * isPressed);
			const double outerKeyHeight = size * (isPressed ? 0.9 : 1.0);
			const double innerKeyHeight = size * 0.8;
			const double innerKeyWidth = size * 0.85;
			const Vec2 innerKeyCenter = center + Vec2::Up(size * 0.08) + Vec2::Down(size * 0.1 * isPressed);
			const double roundRadius = size * 0.1;
			const HSV _keyColor = keyColor;
			const ColorF outerKeyColor = HSV{ _keyColor.h, _keyColor.s, _keyColor.v * 0.8 };
			const DrawableText dtext = font(label);
			const double width = dtext.region().w + size * 0.6;

			if (width > innerKeyWidth)
			{
				const double innerWidth = width - (size - innerKeyWidth);
				RectF{ Arg::center(outerKeyCenter), width, outerKeyHeight }.rounded(roundRadius).draw(outerKeyColor);
				RectF{ Arg::center(innerKeyCenter), innerWidth, innerKeyHeight }.rounded(roundRadius).draw(keyColor);
			}
			else
			{
				RectF{ Arg::center(outerKeyCenter), size, outerKeyHeight }.rounded(roundRadius).draw(outerKeyColor);
				RectF{ Arg::center(innerKeyCenter), innerKeyWidth, innerKeyHeight }.rounded(roundRadius).draw(keyColor);
			}

			dtext.drawAt(innerKeyCenter, labelColor);
		}

		inline void DrawInteractiveAt(const Input& input, const Vec2& center, const Font& font, const double size, const ColorF& keyColor, const ColorF& labelColor, const ColorF& highlightColor)
		{
			DrawAt(input.name(), input.pressed(), center, font, size, (input.pressed() ? highlightColor : keyColor), labelColor);
		}

		inline void DrawAt(const Input& input, const bool isPressed, const Vec2& center, const Font& font, const double size, const ColorF& keyColor, const ColorF& labelColor, const ColorF& highlightColor)
		{
			DrawAt(input.name(), isPressed, center, font, size, (isPressed ? highlightColor : keyColor), labelColor);
		}

		inline void Draw(StringView label, const bool isPressed, const Vec2& pos, const Font& font, const double size, const ColorF& keyColor, const ColorF& labelColor)
		{
			DrawAt(label, isPressed, (pos + GetSize(label, font, size) * 0.5), font, size, keyColor, labelColor);
		}

		inline void DrawInteractive(const Input& input, const Vec2& pos, const Font& font, const double size, const ColorF& keyColor, const ColorF& labelColor, const ColorF& highlightColor)
		{
			DrawAt(input.name(), input.pressed(), (pos + GetSize(input, font, size) * 0.5), font, size, (input.pressed() ? highlightColor : keyColor), labelColor);
		}

		inline void Draw(const Input& input, const bool isPressed, const Vec2& pos, const Font& font, const double size, const ColorF& keyColor, const ColorF& labelColor, const ColorF& highlightColor)
		{
			DrawAt(input.name(), isPressed, (pos + GetSize(input, font, size) * 0.5), font, size, (isPressed ? highlightColor : keyColor), labelColor);
		}

		inline double DrawAsGlyph(const Input& input, const Vec2& pos, const Font& font, const double size, const ColorF& keyColor, const ColorF& labelColor, const ColorF& highlightColor)
		{
			const double w = GetSize(input.name(), font, size).x;
			DrawAt(input.name(), input.pressed(), pos.movedBy(w / 2.0, font.height() / 2.0), font, size, (input.pressed() ? highlightColor : keyColor), labelColor);
			return w;
		}
	}
}
