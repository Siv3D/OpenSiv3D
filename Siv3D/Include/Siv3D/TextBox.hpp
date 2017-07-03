//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "String.hpp"
# include "PointVector.hpp"
# include "Optional.hpp"
# include "Unspecified.hpp"
# include "Mouse.hpp"

namespace s3d
{
	class TextBox
	{
	private:

		class CTextBox;

		std::shared_ptr<CTextBox> pImpl;

	public:

		TextBox();

		TextBox(const Font& font, double x, double y, const Optional<double>& width = unspecified,
			const String& defaultText = L"", const String& description = L"");

		TextBox(const Font& font, const Vec2& pos, const Optional<double>& width = unspecified, 
			const String& defaultText = L"", const String& description = L"")
			: TextBox(font, pos.x, pos.y, width, description, defaultText) {}

		bool update(bool clicked = MouseL.down()) const;

		void drawGlow(double blurRadius = 6, double spread = 3, const ColorF& color = ColorF(0.0, 0.5, 1.0, 0.8)) const;

		void drawBox(const ColorF& boxColor = Palette::White) const;

		void drawText(const ColorF& textColor = Palette::Black, const ColorF& markedTextColor = ColorF(0.33), const ColorF& descriptionColor = ColorF(0.67)) const;

		void draw(const ColorF& boxColor = Palette::White, const ColorF& textColor = Palette::Black,
			double blurRadius = 6, double spread = 3, const ColorF& glowColor = ColorF(0.0, 0.5, 1.0, 0.8)) const;

		bool isActive() const noexcept;

		void setPos(const Vec2& pos) noexcept;

		const Vec2& getPos() const noexcept;

		void setWidth(const Optional<double>& width) noexcept;

		const Optional<double>& getWidth() const noexcept;

		RectF getRect() const noexcept;

		void setText(const String& text);

		const String& getText() const;

		void setDescription(const String& text);

		const String& getDescription() const;
	};
}
