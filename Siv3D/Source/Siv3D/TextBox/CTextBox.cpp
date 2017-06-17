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
# include <Siv3D/Step.hpp>
# include <Siv3D/TextInput.hpp>
# include <Siv3D/Keyboard.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/ViewportBlock2D.hpp>
# include <Siv3D/Transformer2D.hpp>
# include <Siv3D/Print.hpp>

namespace s3d
{
	TextBox::CTextBox::CTextBox(const Font& font, const double x, const double y, const Optional<double>& width, const String& defaultText, const String& description)
		: m_font(font)
		, m_pos(x, y)
		, m_textUTF32(defaultText.toUTF32())
		, m_cursorIndex(m_textUTF32.length())
		, m_description(description)
	{
		m_boxState.width = width;
		updateBox();
	}

	bool TextBox::CTextBox::update(const bool clicked)
	{
		bool hasEvent = false;

		const RectF rect = m_boxState.getRect(m_pos);

		if (m_active)
		{
			const String raw = TextInput::GetRawInput();
			m_cursorIndex = TextInput::UpdateText(m_text, m_cursorIndex, TextInputMode::AllowBackSpace);

			m_textUTF32 = m_text.toUTF32();

			m_markedText = TextInput::GetMarkedText();

			if (!m_markedText &&
				((MouseL.down() && !rect.mouseOver()) || raw.includes(S3DCHAR('\r')) || raw.includes(S3DCHAR('\t'))))
			{
				m_active = false;

				m_cursorIndex = m_textUTF32.length();
			}

			if (!m_markedText)
			{
				if (0 < m_cursorIndex && (KeyLeft.down() || (KeyLeft.pressedDuration() > SecondsF(0.33) && m_leftPress > SecondsF(0.06))))
				{
					--m_cursorIndex;
					m_leftPress.restart();
				}

				if (m_cursorIndex < m_textUTF32.length() && (KeyRight.down() || (KeyRight.pressedDuration() > SecondsF(0.33) && m_rightPress > SecondsF(0.06))))
				{
					++m_cursorIndex;
					m_rightPress.restart();
				}
			}
		}
		else
		{
			if (TextInput::GetMarkedText().isEmpty() && (clicked && rect.mouseOver()))
			{
				hasEvent = true;

				m_active = true;

				m_cursorStopwatch.restart();

				m_cursorIndex = m_textUTF32.length();
			}
		}

		if (m_active && m_markedText.isEmpty() && (clicked && rect.mouseOver()))
		{
			hasEvent = true;

			m_cursorStopwatch.restart();
			m_cursorIndex = m_textUTF32.length();

			const double cursorX = Cursor::PosF().x - m_pos.x - BoxState::PaddingLeft;
			const Array<int32> xAdvances = m_font(m_text).getXAdvances();

			int32 previousX = static_cast<int32>(m_boxState.textOffsetX);
			int32 currentX = previousX;

			for (auto i : step(xAdvances.size()))
			{
				currentX += xAdvances[i];

				if (currentX > cursorX)
				{
					const double t1 = cursorX - previousX;
					const double t2 = currentX - cursorX;
					m_cursorIndex = t1 < t2 ? i : i + 1;
					break;
				}

				previousX = currentX;
			}
		}

		updateBox();

		return hasEvent;
	}

	void TextBox::CTextBox::drawGlow(const double blurRadius, const double spread, const ColorF& color) const
	{
		Transformer2D transformer(Graphics2D::GetTransform().inverse());
		
		if (m_active)
		{
			m_boxState.getRect(m_pos).drawShadow(Vec2(0, 0), blurRadius, spread, color);
		}
	}

	void TextBox::CTextBox::drawBox(const ColorF& boxColor) const
	{
		Transformer2D transformer(Graphics2D::GetTransform().inverse());
		
		const RectF rect = m_boxState.getRect(m_pos);

		rect.draw(boxColor);

		if (!m_active)
		{
			rect.drawFrame(0, 1, Palette::Black);
		}
	}

	void TextBox::CTextBox::drawText(const ColorF& textColor, const ColorF& markedTextColor, const ColorF& descriptionColor) const
	{
		{
			Transformer2D transformer(Graphics2D::GetTransform().inverse());
			
			const double offsetX = m_boxState.textOffsetX;

			ViewportBlock2D viewport(Rect(m_boxState.getRect(m_pos)));

			m_font(m_headText).draw(Vec2(offsetX + BoxState::PaddingLeft, 0), textColor);

			m_font(m_markedText).draw(Vec2(offsetX + BoxState::PaddingLeft + m_boxState.headTextWidth, 0), markedTextColor)
				.bottom().movedBy(0, -2).draw(2, markedTextColor);

			m_font(m_tailText).draw(Vec2(offsetX + BoxState::PaddingLeft + m_boxState.headTextWidth + m_boxState.markedTextWidth, 0), textColor);

			if (m_description && !m_text && !m_active)
			{
				m_font(m_description).draw(Vec2(offsetX + BoxState::PaddingLeft, 0), descriptionColor);
			}

			const bool showCursor = m_active
				&& ((m_cursorStopwatch.ms() % 1200 < 600)
					|| (m_leftPress.isRunning() && m_leftPress < SecondsF(0.5))
					|| (m_rightPress.isRunning() && m_rightPress < SecondsF(0.5)));

			if (showCursor)
			{
				const double x = offsetX + BoxState::PaddingLeft + m_boxState.cursorXAdvance;
				Line(x, 0, x, m_boxState.textHeight).stretched(-3).draw(2, textColor);
			}
		}
	}

	bool TextBox::CTextBox::isActive() const noexcept
	{
		return m_active;
	}

	void TextBox::CTextBox::setPos(const Vec2& pos) noexcept
	{
		m_pos.set(pos);
	}

	const Vec2& TextBox::CTextBox::getPos() const noexcept
	{
		return m_pos;
	}

	void TextBox::CTextBox::setWidth(const Optional<double>& width) noexcept
	{
		m_boxState.width = width;

		updateBox();
	}

	const Optional<double>& TextBox::CTextBox::getWidth() const noexcept
	{
		return m_boxState.width;
	}

	RectF TextBox::CTextBox::getRect() const noexcept
	{
		return m_boxState.getRect(m_pos);
	}

	void TextBox::CTextBox::setText(const String& text)
	{
		m_textUTF32 = text.toUTF32();
		m_cursorIndex = m_textUTF32.length();
		m_text = text;

		updateBox();
	}

	const String& TextBox::CTextBox::getText() const
	{
		return m_text;
	}

	void TextBox::CTextBox::setDescription(const String& text)
	{
		m_description = text;

		updateBox();
	}

	const String& TextBox::CTextBox::getDescription() const
	{
		return m_description;
	}

	void TextBox::CTextBox::updateBox()
	{
		m_text = CharacterSet::FromUTF32(m_textUTF32);
		m_headText = CharacterSet::FromUTF32(m_textUTF32.substr(0, m_cursorIndex));
		m_tailText = CharacterSet::FromUTF32(m_textUTF32.substr(m_cursorIndex, std::u32string::npos));

		m_boxState.headTextWidth = m_font(m_headText).region().w;
		m_boxState.tailTextWidth = m_font(m_tailText).region().w;
		m_boxState.markedTextWidth = m_font(m_markedText).region().w;
		m_boxState.textHeight = m_font.height();
		m_boxState.textOffsetX = std::min(0.0, m_boxState.getWidth() - (m_boxState.headTextWidth + m_boxState.markedTextWidth + m_boxState.tailTextWidth));

		const Array<int32> xAdvances = m_font(m_text).getXAdvances();
		const Array<int32> markedXAdvances = m_font(m_markedText).getXAdvances();
		m_boxState.cursorXAdvance = 0;

		for (auto i : step(m_cursorIndex))
		{
			m_boxState.cursorXAdvance += xAdvances[i];
		}

		for (auto xAdvance : markedXAdvances)
		{
			m_boxState.cursorXAdvance += xAdvance;
		}

		const double offsetT = m_boxState.textOffsetX + m_boxState.cursorXAdvance;
		const double width = m_boxState.getWidth() - BoxState::PaddingLeft - BoxState::PaddingRight;
	
		if (offsetT < 0)
		{
			m_boxState.textOffsetX -= offsetT;
		}
		else if (offsetT > width)
		{
			m_boxState.textOffsetX -= (offsetT - width);
		}

		if (m_description && !m_text && !m_active)
		{
			m_boxState.descriptionTextWidth = m_font(m_description).region().w;
		}
		else
		{
			m_boxState.descriptionTextWidth = 0.0;
		}
	}
}
