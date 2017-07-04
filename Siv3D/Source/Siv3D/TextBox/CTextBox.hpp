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
# include <Siv3D/TextBox.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/Stopwatch.hpp>

namespace s3d
{
	class TextBox::CTextBox
	{
	private:

		Font m_font;

		Vec2 m_pos = { 0, 0 };

		bool m_active = false;

		std::u32string m_textUTF32;

		String m_text;

		String m_headText;

		String m_markedText;

		String m_tailText;

		String m_description;

		size_t m_cursorIndex = 0;

		Stopwatch m_leftPress;

		Stopwatch m_rightPress;

		Stopwatch m_cursorStopwatch;

		struct BoxState
		{
			double headTextWidth = 0.0;

			double tailTextWidth = 0.0;

			double markedTextWidth = 0.0;

			double descriptionTextWidth = 0.0;

			double textHeight = 0.0;

			double textOffsetX = 0.0;

			double cursorXAdvance = 0;

			Optional<double> width;

			static constexpr int32 PaddingLeft = 6;

			static constexpr int32 PaddingRight = 8;

			double getWidth() const noexcept
			{
				const double contentWidth = PaddingLeft + headTextWidth + markedTextWidth + tailTextWidth + descriptionTextWidth + PaddingRight;

				return width.value_or(contentWidth);
			}

			RectF getRect(const Vec2& pos) const noexcept
			{
				return RectF(pos, getWidth(), textHeight);
			}

		} m_boxState;

		void updateBox();

	public:

		CTextBox() = default;

		CTextBox(const Font& font, double x, double y, const Optional<double>& width, const String& defaultText, const String& description);

		bool update(bool clicked);

		void drawGlow(double blurRadius, double spread, const ColorF& color) const;

		void drawBox(const ColorF& boxColor) const;

		void drawText(const ColorF& textColor, const ColorF& markedTextColor, const ColorF& descriptionColor) const;

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
