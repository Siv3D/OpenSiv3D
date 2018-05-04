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

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "String.hpp"
# include "Optional.hpp"
# include "Unspecified.hpp"
# include "Mouse.hpp"
# include "Color.hpp"

namespace s3d
{
	class TextBox
	{
	private:

		class CTextBox;

		std::shared_ptr<CTextBox> pImpl;

	public:

		struct Style
		{
			ColorF boxColor = Palette::White;

			ColorF borderColor = ColorF(0.25);

			ColorF textColor = Palette::Black;

			ColorF glowColor = ColorF(0.0, 0.5, 1.0, 0.8);

			double blurRadius = 6;

			double spread = 3;
			
			Style() = default;
			
			static Style Default()
			{
				return Style{};
			}
		};

		enum class State
		{
			Active,

			Inactive,

			Enter,

			Tab,

			ShiftTab,
		};

		TextBox();

		TextBox(const Font& font,
			const Vec2& pos,
			double boxWidth = 200.0,
			const Optional<size_t>& maxChars = unspecified,
			const String& defaultText = U"");

		TextBox(const Font& font,
			const Arg::center_<Vec2> center,
			double boxWidth = 200.0,
			const Optional<size_t>& maxChars = unspecified,
			const String& defaultText = U"");

		~TextBox();

		State update(bool clicked = MouseL.down());

		void draw(const Style& style = Style::Default()) const;

		void drawOverlay(const Style& style = Style::Default()) const;

		void setActive(bool active);

		[[nodiscard]] bool isActive() const;

		[[nodiscard]] const RectF& getRect() const;

		void setPos(const Vec2& pos);

		void setCenter(const Vec2& center);

		void setText(const String& text);

		[[nodiscard]] const String& getText() const;

		[[nodiscard]] size_t getCursorIndex() const;
	};
}
