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

# include "CTextBox.hpp"
# include <Siv3D/TextInput.hpp>
# include <Siv3D/Keyboard.hpp>

namespace s3d
{
	TextBox::CTextBox::CTextBox()
	{

	}

	TextBox::CTextBox::CTextBox(const Font& font, const RectF& rect, const Optional<size_t>& maxChars, const String& defaultText)
		: m_font(font)
		, m_rect(rect)
		, m_maxChars(maxChars)
		, m_text(defaultText)
		, m_cursorIndex(defaultText.length())
		, m_cursorStopwatch(true)
		, m_initialized(true)
	{
	
	}

	TextBox::CTextBox::~CTextBox()
	{

	}

	TextBox::State TextBox::CTextBox::update(const bool clicked)
	{
		if (!m_initialized)
		{
			return State::Inactive;
		}

		if (clicked)
		{
			m_active = m_rect.mouseOver();
		}

		if (m_active)
		{
			const String raw = TextInput::GetRawInput();

			m_cursorIndex = TextInput::UpdateText(m_text, m_cursorIndex, TextInputMode::AllowBackSpaceDelete);

			if (m_maxChars && m_text.length() > m_maxChars.value())
			{
				m_text.resize(m_maxChars.value());

				m_cursorIndex = std::min(m_cursorIndex, m_text.length());
			}

			if (0 < m_cursorIndex && (KeyLeft.down() || (KeyLeft.pressedDuration() > SecondsF(0.33) && m_leftPressStopwatch > SecondsF(0.06))))
			{
				--m_cursorIndex;
				m_leftPressStopwatch.restart();
			}

			if (m_cursorIndex < m_text.length() && (KeyRight.down() || (KeyRight.pressedDuration() > SecondsF(0.33) && m_rightPressStopwatch > SecondsF(0.06))))
			{
				++m_cursorIndex;
				m_rightPressStopwatch.restart();
			}

			if (raw.includes(U'\r'))
			{
				setActive(false);

				return State::Enter;
			}
			else if (raw.includes(U'\t'))
			{
				setActive(false);

				return KeyShift.pressed() ? State::ShiftTab : State::Tab;
			}

			return State::Active;
		}
		else
		{
			return State::Inactive;
		}
	}

	void TextBox::CTextBox::draw(const Style& style = Style()) const
	{
		if (!m_initialized)
		{
			return;
		}

		if (!m_active)
		{
			drawGlow(style);

			drawBox(style);

			drawText(style);
		}
	}

	void TextBox::CTextBox::drawOverlay(const Style& style = Style()) const
	{
		if (!m_initialized)
		{
			return;
		}

		if (m_active)
		{
			drawGlow(style);

			drawBox(style);

			drawTextActive(style);
		}
	}

	void TextBox::CTextBox::setActive(const bool active)
	{
		if ((active == false) && m_locked)
		{
			return;
		}

		if ((m_active == false) && (active == true))
		{
			m_cursorIndex = m_text.length();
		}

		m_active = active;
	}

	bool TextBox::CTextBox::isActive() const
	{
		return m_active;
	}

	const RectF& TextBox::CTextBox::getRect() const
	{
		return m_rect;
	}

	void TextBox::CTextBox::setPos(const Vec2& pos)
	{
		m_rect.setPos(pos);
	}

	void TextBox::CTextBox::setCenter(const Vec2& center)
	{
		m_rect.setCenter(center);
	}

	void TextBox::CTextBox::setText(const String& text)
	{
		m_text = text;
	}

	const String& TextBox::CTextBox::getText() const
	{
		return m_text;
	}

	void TextBox::CTextBox::drawGlow(const Style& style) const
	{
		if (m_active)
		{
			m_rect.drawShadow(Vec2(0, 0), style.blurRadius, style.spread, style.glowColor);
		}
	}

	void TextBox::CTextBox::drawBox(const Style& style) const
	{
		m_rect.draw(style.boxColor);

		m_rect.drawFrame(1, 0, style.borderColor);
	}

	void TextBox::CTextBox::drawCursor(const Vec2& pos, const double fontHeight, const ColorF& textColor) const
	{
		if (!m_active)
		{
			return;
		}

		const bool showCursor = ((m_cursorStopwatch.ms() % 1200 < 600)
			|| (m_leftPressStopwatch.isRunning() && m_leftPressStopwatch < SecondsF(0.5))
			|| (m_rightPressStopwatch.isRunning() && m_rightPressStopwatch < SecondsF(0.5)));

		if (showCursor)
		{
			Line(pos.x, pos.y, pos.x, pos.y + fontHeight).stretched(-2).draw(2, textColor);
		}
	}

	void TextBox::CTextBox::drawText(const Style& style) const
	{
		Vec2 penPos(m_rect.pos + Vec2(1 + m_rect.h * 0.16, 1));

		for (const auto& glyph : m_font(m_text))
		{
			glyph.texture.drawClipped(penPos + glyph.offset, m_rect, style.textColor);

			penPos.x += glyph.xAdvance;
		}
	}

	void TextBox::CTextBox::drawTextActive(const Style& style) const
	{
		const int32 fontHeight = m_font.height();
		const Vec2 candidateWindowPosOffset(0, 4);

		const String textHeader = m_text.substr(0, m_cursorIndex);
		const String textTail = m_text.substr(m_cursorIndex, String::npos);
		const String editingText = TextInput::GetEditingText();

	# if defined(SIV3D_TARGET_WINDOWS)
	
		const auto[editingCursorIndex, editingTargetlength] = win::TextInput::GetCursorIndex();
		const bool hasEditingTarget = (editingTargetlength > 0);

	# else
	
		const int32 editingCursorIndex = -1, editingTargetlength = 0;
		const bool hasEditingTarget = false;

	# endif

		m_locked = !editingText.isEmpty();

		const double right = m_rect.x + m_rect.w;
		Vec2 pos(m_rect.pos + Vec2(1 + m_rect.h * 0.16, 1));

		for (auto glyph : m_font(textHeader))
		{
			glyph.texture.draw(pos + glyph.offset, style.textColor);
			pos.x += glyph.xAdvance;
		}

		double begX = pos.x, begY = 0, endX = pos.x;

		for (auto glyph : m_font(editingText))
		{
			if (glyph.index == editingCursorIndex)
			{
				begX = pos.x;
				begY = pos.y + fontHeight;
			}
			else if (hasEditingTarget && glyph.index == editingCursorIndex + editingTargetlength - 1)
			{
				endX = pos.x + glyph.xAdvance;
			}

			glyph.texture.draw(pos + glyph.offset, style.textColor);
			pos.x += glyph.xAdvance;
		}

		if (hasEditingTarget)
		{
			Line(begX, begY, endX, begY).movedBy(0, -2).draw(2, style.textColor);
		}

		drawCursor(pos, fontHeight, style.textColor);

		for (auto glyph : m_font(textTail))
		{
			glyph.texture.draw(pos + glyph.offset, style.textColor);
			pos.x += glyph.xAdvance;
		}

	# if defined(SIV3D_TARGET_WINDOWS)

		win::TextInput::DrawCandidateWindow(m_font, Vec2(begX + candidateWindowPosOffset.x * hasEditingTarget, pos.y + fontHeight + candidateWindowPosOffset.y));

	# endif
	}
}
