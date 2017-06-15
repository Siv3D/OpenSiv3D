# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.7, 0.9, 0.5));

	const Font font(20);

	Array<TextBox> textboxes = {
		TextBox(font, 50, 50, 300, L"", L"東京都 渋谷区 3 丁目"),
		TextBox(font, 50, 100, 300, L"", L"000-0000"),
		TextBox(font, 50, 150, 300),
		TextBox(font, 50, 200),
	};

	while (System::Update())
	{
		for (auto& textbox : textboxes)
		{
			textbox.update();

			textbox.draw();
		}
	}
}
