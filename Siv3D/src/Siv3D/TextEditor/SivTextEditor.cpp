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

# include <Siv3D/TextEditor.hpp>
# include <Siv3D/TextInput.hpp>
# include <Siv3D/Keyboard.hpp>
# include <Siv3D/Line.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/Utility.hpp>
# include <Siv3D/Indexed.hpp>

namespace s3d
{
	TextEditor::TextEditor(const bool active)
		: m_cursorStopwatch(true)
		, m_active(active)
	{
	
	}

	void TextEditor::update(const Font& font,
		const Font& fontCabdidate,
		const RectF& rect,
		const ColorF& textColor,
		const ColorF& editingTextColor,
		const TextInputMode mode)
	{
		if (m_active)
		{
			m_cursorIndex = TextInput::UpdateText(m_text, m_cursorIndex, mode);

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
		}

		drawText(font, fontCabdidate, rect, textColor, editingTextColor);
	}

	void TextEditor::setActive(bool active) noexcept
	{
		if (isLocked() & (active == false))
		{
			return;
		}

		m_active = active;
	}

	bool TextEditor::isActive() const noexcept
	{
		return m_active;
	}

	bool TextEditor::isLocked() const noexcept
	{
		return m_active && m_locked;
	}
	
	void TextEditor::drawCursor(const Vec2& pos, double fontHeight, const ColorF& textColor) const
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
			Line(pos.x, pos.y, pos.x, pos.y + fontHeight).draw(2, textColor);
		}
	}

	void TextEditor::drawText(const Font& font,
		const Font& fontCabdidate,
		const RectF& rect,
		const ColorF& textColor,
		const ColorF& editingTextColor)
	{
		const int32 fontHeight = font.height();
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

		const double right = rect.x + rect.w;
		Vec2 pos(rect.pos);

		for (auto glyph : font(textHeader))
		{
			if (glyph.codePoint == U'\n'
				|| ((glyph.xAdvance <= rect.w) && (right < pos.x + glyph.xAdvance)))
			{
				pos.x = rect.x;
				pos.y += fontHeight;
			}

			glyph.texture.draw(pos + glyph.offset, textColor);
			pos.x += glyph.xAdvance;
		}

		double begX = pos.x, begY = 0, endX = pos.x;

		for (auto glyph : font(editingText))
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

			glyph.texture.draw(pos + glyph.offset, editingTextColor);
			pos.x += glyph.xAdvance;
		}

		if (hasEditingTarget)
		{
			Line(begX, begY, endX, begY).draw(2, editingTextColor);
		}

		drawCursor(pos, fontHeight, textColor);

		for (auto glyph : font(textTail))
		{
			if (glyph.codePoint == U'\n'
				|| ((glyph.xAdvance <= rect.w) && (right < pos.x + glyph.xAdvance)))
			{
				pos.x = rect.x;
				pos.y += fontHeight;
			}

			glyph.texture.draw(pos + glyph.offset, textColor);
			pos.x += glyph.xAdvance;
		}

	# if defined(SIV3D_TARGET_WINDOWS)

		win::TextInput::DrawCandidateWindow(fontCabdidate, Vec2(begX + candidateWindowPosOffset.x * hasEditingTarget, pos.y + fontHeight + candidateWindowPosOffset.y));

	# endif
	}
}
