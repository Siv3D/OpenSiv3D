//-----------------------------------------------
//
//	This file is part of the Siv3D HamFramework.
//
//	Copyright (C) 2014-2019 HAMSTRO
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D.hpp>

namespace s3d
{
	namespace InputDeviceSymbol
	{
		[[nodiscard]] inline Vec2 GetSize(const String& text, const Font& font, double size)
		{
			const double innerSize = size * 0.8;
			const double width = font(text).region().w + size * 0.6;
			return Vec2(width > innerSize ? width : size, size);
		}

		[[nodiscard]] inline Vec2 GetSize(const Key& key, const Font& font, double size)
		{
			return GetSize(key.name(), font, size);
		}

		inline void DrawAt(const String& label, bool isPressed, const Vec2& center, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black)
		{
			const Vec2 outerKeyCenter = center + Vec2::Down(size * 0.1 * 0.5 * isPressed);
			const double outerKeyHeight = size * (isPressed ? 0.9 : 1.0);
			const double innerKeyHeight = size * 0.8;
			const double innerKeyWidth = size * 0.85;
			const Vec2 innerKeyCenter = center + Vec2::Up(size * 0.05) + Vec2::Down(size * 0.1 * isPressed);
			const double roundRadius = size * 0.1;
			const HSV _keyColor = keyColor;
			const ColorF outerKeyColor = HSV(_keyColor.h, _keyColor.s, _keyColor.v * 0.8);
			const double width = font(label).region().w + size * 0.6;

			if (width > innerKeyWidth)
			{
				const double innerWidth = width - (size - innerKeyWidth);
				RectF(Arg::center(outerKeyCenter), Vec2(width, outerKeyHeight)).rounded(roundRadius).draw(outerKeyColor);
				RectF(Arg::center(innerKeyCenter), Vec2(innerWidth, innerKeyHeight)).rounded(roundRadius).draw(keyColor);
			}
			else
			{
				RectF(Arg::center(outerKeyCenter), size, outerKeyHeight).rounded(roundRadius).draw(outerKeyColor);
				RectF(Arg::center(innerKeyCenter), Vec2(innerKeyWidth, innerKeyHeight)).rounded(roundRadius).draw(keyColor);
			}

			font(label).drawAt(innerKeyCenter, labelColor);
		}

		inline void DrawInteractiveAt(const Key& key, const Vec2& center, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black, const ColorF& highlightColor = ColorF(1.0, 0.6, 0.6))
		{
			DrawAt(key.name(), key.pressed(), center, font, size, key.pressed() ? highlightColor : keyColor, labelColor);
		}

		inline void DrawAt(const Key& key, bool isPressed, const Vec2& center, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black, const ColorF& highlightColor = ColorF(1.0, 0.6, 0.6))
		{
			DrawAt(key.name(), isPressed, center, font, size, isPressed ? highlightColor : keyColor, labelColor);
		}

		inline void Draw(const String& label, bool isPressed, const Vec2& pos, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black)
		{
			DrawAt(label, isPressed, pos + GetSize(label, font, size) * 0.5, font, size, keyColor, labelColor);
		}

		inline void DrawInteractive(const Key& key, const Vec2& pos, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black, const ColorF& highlightColor = ColorF(1.0, 0.6, 0.6))
		{
			DrawAt(key.name(), key.pressed(), pos + GetSize(key, font, size) * 0.5, font, size, key.pressed() ? highlightColor : keyColor, labelColor);
		}

		inline void Draw(const Key& key, bool isPressed, const Vec2& pos, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black, const ColorF& highlightColor = ColorF(1.0, 0.6, 0.6))
		{
			DrawAt(key.name(), isPressed, pos + GetSize(key, font, size) * 0.5, font, size, isPressed ? highlightColor : keyColor, labelColor);
		}

		inline double DrawAsGlyph(const Key& key, const Vec2& pos, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black, const ColorF& highlightColor = ColorF(1.0, 0.6, 0.6))
		{
			const double w = GetSize(key.name(), font, size).x;
			DrawAt(key.name(), key.pressed(), pos.movedBy(w / 2, font.height() / 2), font, size, key.pressed() ? highlightColor : keyColor, labelColor);
			return w;
		}
	}
}

/* example

# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Scene::SetBackground(Palette::Seagreen);

	const Font font(30, Typeface::Medium);
	const double keySize = font.fontSize() * 1.5;

	while (System::Update())
	{
		Vec2 penPos(40, 40);

		for (const auto& glyph : font(U"$ OK  % Cancel  @ Menu"))
		{
			if (glyph.codePoint == U'$')
			{
				penPos.x += InputDeviceSymbol::DrawAsGlyph(KeyZ, penPos, font, keySize);
				continue;
			}
			else if (glyph.codePoint == U'%')
			{
				penPos.x += InputDeviceSymbol::DrawAsGlyph(KeyX, penPos, font, keySize);
				continue;
			}
			else if (glyph.codePoint == U'@')
			{
				penPos.x += InputDeviceSymbol::DrawAsGlyph(KeyC, penPos, font, keySize);
				continue;
			}

			glyph.texture.draw(penPos + glyph.offset);
			penPos.x += glyph.xAdvance;
		}

		InputDeviceSymbol::DrawInteractive(KeyF2, Vec2(100, 200), font, keySize);
		InputDeviceSymbol::DrawInteractive(KeyUp, Vec2(100, 250), font, keySize);
		InputDeviceSymbol::DrawInteractive(KeyEnter, Vec2(100, 300), font, keySize);
		InputDeviceSymbol::DrawInteractive(KeyBackspace, Vec2(100, 350), font, keySize);
	}
}

*/
