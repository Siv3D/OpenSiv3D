# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.9));

	const Font font(20);

	Array<TextBox> textBoxes;
	textBoxes.emplace_back(font, Vec2(100, 100), 200);
	textBoxes.emplace_back(font, Vec2(100, 200), 200);
	textBoxes.emplace_back(font, Vec2(100, 300), 200);

	size_t activeIndex = 0;
	textBoxes[activeIndex].setActive(true);

	while (System::Update())
	{
		for (size_t i : step(textBoxes.size()))
		{
			auto& textBox = textBoxes[i];

			textBox.update();

			if (textBox.isActive())
			{
				activeIndex = i;

				if (!textBox.hasMarkedText() && KeyTab.down())
				{
					textBoxes[activeIndex].setActive(false);

					++activeIndex %= textBoxes.size();

					Print << textBoxes[activeIndex].setActive(true);

					break;
				}
			}
		}
	
		for (const auto& textBox : textBoxes)
		{
			textBox.draw();
		}
	}
}