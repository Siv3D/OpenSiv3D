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
# include <Siv3D/TextBox.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/Stopwatch.hpp>

namespace s3d
{
	class TextBox::CTextBox
	{
	private:

		Font m_font;

		RectF m_rect = RectF(0);

		Optional<size_t> m_maxChars;

		String m_text;
	
		size_t m_cursorIndex = 0;

		Stopwatch m_leftPressStopwatch, m_rightPressStopwatch, m_cursorStopwatch;

		bool m_active = false;

		mutable bool m_locked = false;

		bool m_initialized = false;

		void drawGlow(const Style& style) const;

		void drawBox(const Style& style) const;

		void drawCursor(const Vec2& pos, double fontHeight, const ColorF& textColor) const;

		void drawText(const Style& style) const;

		void drawTextActive(const Style& style) const;

	public:

		CTextBox();

		CTextBox(const Font& font, const RectF& rect, const Optional<size_t>& maxChars, const String& defaultText);

		~CTextBox();

		State update(bool clicked);

		void draw(const Style& style) const;

		void drawOverlay(const Style& style) const;

		void setActive(bool active);

		bool isActive() const;

		const RectF& getRect() const;

		void setPos(const Vec2& pos);

		void setCenter(const Vec2& center);

		void setText(const String& text);

		const String& getText() const;

		size_t getCursorIndex() const;
	};
}
