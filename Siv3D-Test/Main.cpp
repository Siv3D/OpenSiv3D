
# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	Graphics::SetBackground(ColorF(1.0));

	const Font font(24);
	const Font font2(18);
	TextEditor editor(true);

	String text;
	size_t cursorPos = 0;

	while (System::Update())
	{
		const RectF rect(10, 50, 200, 200);

		rect.draw(ColorF(0.9));

		editor.update(font, font2, rect);

		if (editor.isLocked())
		{
			Circle(400, 400, 80).draw(Palette::Red);
		}
	}
}
