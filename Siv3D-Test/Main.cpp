# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(1.0));
	const Font font(24);
	const Point pos(10, 10);
	String text;
	size_t cursorIndex = 0;
	Stopwatch leftPress, rightPress, upPress, downPress;

	while (System::Update())
	{
		cursorIndex = TextInput::UpdateText(text, cursorIndex);
		const String markedText = TextInput::GetMarkedText();
		const std::u32string textUTF32 = text.toUTF32();
		const Array<int32> xAdvances = font(text).getXAdvances();
		int32 requestUpDown = 0;

		if (!markedText)
		{
			if (0 < cursorIndex && (KeyLeft.down() || (KeyLeft.pressedDuration() > 0.33s && leftPress > 0.06s)))
			{
				--cursorIndex;
				leftPress.restart();
			}

			if (cursorIndex < textUTF32.size() && (KeyRight.down() || (KeyRight.pressedDuration() > 0.33s && rightPress > 0.06s)))
			{
				++cursorIndex;
				rightPress.restart();
			}

			if (KeyUp.down())
			{
				requestUpDown = -1;
				upPress.restart();
			}

			if (KeyDown.down())
			{
				requestUpDown = 1;
				downPress.restart();
			}
		}
	
		Point cursorPos(0, 0);
		int32 xOffset = 0;

		if (0 < cursorIndex)
		{
			Point charPos(0, 0);
			size_t index = 0;

			for (const auto ch : textUTF32)
			{
				if (ch == U'\n')
				{
					charPos.set(0, charPos.y + 1);
					xOffset = 0;
				}
				else
				{
					++charPos.x;
					xOffset += xAdvances[index];
				}

				if (++index == cursorIndex)
				{
					cursorPos = charPos;
					break;
				}
			}
		}

		if (requestUpDown)
		{
			Point charPos(0, 0);
			size_t index = 0;
			bool onTargetLine = false;
	
			for (const auto ch : textUTF32)
			{
				if (!onTargetLine && charPos.y == cursorPos.y + requestUpDown)
				{
					if (charPos.x == cursorPos.x)
					{
						cursorIndex = index;
						break;
					}

					onTargetLine = true;
				}

				if (ch == U'\n')
				{
					charPos.set(0, charPos.y + 1);

					if (onTargetLine)
					{
						cursorIndex = index;
						onTargetLine = false;
						break;
					}
				}
				else
				{
					++charPos.x;
				}

				++index;

				if (onTargetLine && charPos.x == cursorPos.x)
				{
					cursorIndex = index;
					onTargetLine = false;
					break;
				}
			}

			if (onTargetLine)
			{
				cursorIndex = index;
			}
		}

		const int32 yOffset = cursorPos.y * font.height();
		font(text).draw(pos, Palette::Black);
		font(markedText).draw(Point(xOffset, yOffset).movedBy(pos), Palette::Gray)
			.bottom().movedBy(1, -2.0).draw(2, Palette::Gray);

		for (const int32 xAdvance : font(markedText).getXAdvances())
		{
			xOffset += xAdvance;
		}

		Rect(xOffset - 1, yOffset, 1, font.height()).movedBy(pos).draw(Palette::Black);
	}
}
