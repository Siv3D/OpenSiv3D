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
# include <Siv3D/Common.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/DrawableText.hpp>
# include <Siv3D/Input.hpp>

namespace s3d
{
	namespace InputIcon
	{
		inline constexpr ColorF DefaultHighlightColor{ 1.0, 0.6, 0.6 };

		[[nodiscard]]
		inline Vec2 GetSize(const String& text, const Font& font, double size);

		[[nodiscard]]
		inline Vec2 GetSize(const Input& input, const Font& font, double size);

		inline void DrawAt(const String& label, bool isPressed, const Vec2& center, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black);

		inline void DrawInteractiveAt(const Input& input, const Vec2& center, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black, const ColorF& highlightColor = DefaultHighlightColor);

		inline void DrawAt(const Input& input, bool isPressed, const Vec2& center, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black, const ColorF& highlightColor = DefaultHighlightColor);

		inline void Draw(const String& label, bool isPressed, const Vec2& pos, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black);

		inline void DrawInteractive(const Input& input, const Vec2& pos, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black, const ColorF& highlightColor = DefaultHighlightColor);

		inline void Draw(const Input& input, bool isPressed, const Vec2& pos, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black, const ColorF& highlightColor = DefaultHighlightColor);

		inline double DrawAsGlyph(const Input& input, const Vec2& pos, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black, const ColorF& highlightColor = DefaultHighlightColor);
	}
}

# include "detail/InputIcon.ipp"

/*

// example

# include <Siv3D.hpp>
# include <Siv3D/Experimental/InputIcon.hpp>

void Main()
{
	Scene::SetBackground(Palette::Seagreen);
	const Font font{ 30, Typeface::Medium };
	const double keySize = (font.fontSize() * 1.5);

	while (System::Update())
	{
		InputIcon::DrawInteractive(KeyA, Vec2{ 100, 50 }, font, keySize);
		InputIcon::DrawInteractive(KeyB, Vec2{ 200, 50 }, font, keySize);
		InputIcon::DrawInteractive(MouseL, Vec2{ 300, 50 }, font, keySize);

		InputIcon::DrawInteractive(KeyF2, Vec2{ 100, 150 }, font, keySize);
		InputIcon::DrawInteractive(KeyUp, Vec2{ 100, 250 }, font, keySize);
		InputIcon::DrawInteractive(KeyEnter, Vec2{ 100, 350 }, font, keySize);
		InputIcon::DrawInteractive(KeyBackspace, Vec2{ 100, 450 }, font, keySize);
	}
}

*/
