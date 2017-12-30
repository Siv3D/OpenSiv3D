# include <Siv3D.hpp>

class TextBox
{
public:

	struct Style
	{
		ColorF boxColor = Palette::White;

		ColorF borderColor = ColorF(0.25);

		ColorF textColor = Palette::Black;

		ColorF glowColor = ColorF(0.0, 0.5, 1.0, 0.8);

		double blurRadius = 6;

		double spread = 3;
	};

	enum class State
	{
		Active,

		Inactive,

		Enter,

		Tab,

		ShiftTab,
	};

private:

	Font m_font;

	RectF m_rect = RectF(0);

	String m_text;

	size_t m_cursorIndex = 0;

	Stopwatch m_leftPressStopwatch, m_rightPressStopwatch, m_cursorStopwatch;

	bool m_active = false;

	mutable bool m_locked = false;

	bool m_initialized = false;

	void drawGlow(const Style& style) const
	{
		if (m_active)
		{
			m_rect.drawShadow(Vec2(0, 0), style.blurRadius, style.spread, style.glowColor);
		}
	}

	void drawBox(const Style& style) const
	{
		m_rect.draw(style.boxColor);

		m_rect.drawFrame(1, 0, style.borderColor);
	}

	void drawCursor(const Vec2& pos, const double fontHeight, const ColorF& textColor) const
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

	void drawText(const Style& style) const
	{
		Vec2 penPos(m_rect.pos + Vec2(1 + m_rect.h * 0.16, 1));

		for (const auto& glyph : m_font(m_text))
		{
			glyph.texture.drawClipped(penPos + glyph.offset, m_rect, style.textColor);

			penPos.x += glyph.xAdvance;
		}
	}

	void drawTextActive(const Style& style) const
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

		DrawCandidateWindow(m_font, Vec2(begX + candidateWindowPosOffset.x * hasEditingTarget, pos.y + fontHeight + candidateWindowPosOffset.y));

	# endif
	}

# if defined(SIV3D_TARGET_WINDOWS)

	static void DrawCandidateWindow(const Font& font,
		const Vec2& basePos,
		const ColorF& candidateBoxColor = ColorF(1.0),
		const ColorF& candidateSelectedBackgroundColor = ColorF(0.55, 0.85, 1.0),
		const ColorF& candidateBoxFrameColor = ColorF(0.75),
		const ColorF& candidateTextColor = ColorF(0.0))
	{
		const double candidatesMargin = 4.0;
		const String editingText = TextInput::GetEditingText();
		const auto[editingCursorIndex, editingTargetlength] = win::TextInput::GetCursorIndex();
		const bool hasEditingTarget = (editingTargetlength > 0);
		const String editingTargetText = editingText.substr(editingCursorIndex, editingTargetlength);
		const auto cadidates = win::TextInput::GetCandidates();
		const double candidateItemHeight = font.height() + candidatesMargin;

		double boxWidth = 0.0;

		for (const auto& canditate : cadidates)
		{
			boxWidth = Max(boxWidth, font(canditate).region().w);
		}

		const double leftOffset = hasEditingTarget ? font(U"1  ").region().w : 0.0;
		const Vec2 boxPos(Clamp(basePos.x - leftOffset, 7.0, Window::Width() - boxWidth - leftOffset - 12.0), basePos.y);

		boxWidth += leftOffset + 5;

		if (cadidates)
		{
			RectF(boxPos, boxWidth, candidateItemHeight * cadidates.size()).stretched(5, 0)
				.draw(candidateBoxColor).drawFrame(1, 0, candidateBoxFrameColor);
		}

		for (auto[i, text] : Indexed(cadidates))
		{
			bool selected = false;

			if (editingTargetText == text)
			{
				selected = true;

				RectF(boxPos.x, boxPos.y + i * candidateItemHeight, boxWidth, candidateItemHeight)
					.stretched(5, 0).draw(candidateSelectedBackgroundColor);
			}

			if (text)
			{
				const Vec2 posNumber(boxPos.x, boxPos.y + i * candidateItemHeight + (candidatesMargin) / 2);
				const Vec2 posLabel(posNumber.x + leftOffset, posNumber.y);

				if (hasEditingTarget)
				{
					font(i + 1).draw(posNumber, candidateTextColor);
				}

				font(text).draw(posLabel, candidateTextColor);
			}
		}
	}

# endif

public:

	TextBox() = default;

	TextBox(const Font& font,
		const Vec2& pos,
		double boxWidth = 200.0,
		const String& defaultText = U"")
		: m_font(font)
		, m_rect(pos, boxWidth, font.height() + 2)
		, m_text(defaultText)
		, m_cursorIndex(defaultText.length())
		, m_cursorStopwatch(true)
		, m_initialized(true) {}

	TextBox(const Font& font,
		const Arg::center_<Vec2> center,
		double boxWidth = 200.0,
		const String& defaultText = U"")
		: m_font(font)
		, m_rect(center, boxWidth, font.height() + 2)
		, m_text(defaultText)
		, m_cursorIndex(defaultText.length())
		, m_cursorStopwatch(true)
		, m_initialized(true) {}

	State update(bool clicked = MouseL.down())
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

	void draw(const Style& style = Style()) const
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

	void drawOverlay(const Style& style = Style()) const
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

	void setActive(bool active)
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

	bool isActive() const
	{
		return m_active;
	}

	const RectF& getRect() const
	{
		return m_rect;
	}

	void setPos(const Vec2& pos)
	{
		m_rect.setPos(pos);
	}

	void setCenter(const Vec2& center)
	{
		m_rect.setCenter(center);
	}

	void setText(const String& text)
	{
		m_text = text;
	}

	const String& getText() const
	{
		return m_text;
	}
};

void Main()
{
	Graphics::SetBackground(ColorF(0.8, 0.9, 1.0));
	const Font font(25);

	Array<TextBox> textBoxes;
	textBoxes << TextBox(font, Vec2(80, 100), 200, U"");
	textBoxes << TextBox(font, Vec2(80, 150), 200, U"");
	textBoxes << TextBox(font, Vec2(80, 200), 200, U"");
	textBoxes << TextBox(font, Vec2(80, 250), 200, U"");

	while (System::Update())
	{
		{
			size_t index = 0;

			for (auto& textBox : textBoxes)
			{
				const auto result = textBox.update();

				if ((index + 1) < textBoxes.size() &&
					(result == TextBox::State::Tab || result == TextBox::State::Enter))
				{
					textBoxes[index + 1].setActive(true);
					break;
				}
				else if (index > 0 &&
					result == TextBox::State::ShiftTab)
				{
					textBoxes[index - 1].setActive(true);
					break;
				}

				++index;
			}
		}

		for (const auto& textBox : textBoxes)
		{
			textBox.draw();
		}

		for (const auto& textBox : textBoxes)
		{
			textBox.drawOverlay();
		}
	}
}
