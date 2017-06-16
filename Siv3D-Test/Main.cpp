# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.7, 0.9, 0.5));

	const Font font(20);
	TextBox textbox(font, 30, 30, 200, L"", L"");

	while (System::Update())
	{
		textbox.update();
		textbox.draw();
	}
}
