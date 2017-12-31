# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.8, 0.9, 1.0));
	const Font font(25);

	Array<TextBox> textBoxes;
	textBoxes << TextBox(font, Vec2(50, 50), 200);
	textBoxes << TextBox(font, Vec2(50, 100), 300);
	textBoxes << TextBox(font, Vec2(50, 150), 200, 4); // 最大文字数を 4 文字に制限
	textBoxes << TextBox(font, Vec2(50, 200), 200, none, U"Name"); // "Hello" をデフォルトのテキストに

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
