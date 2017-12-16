
# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	Graphics::SetBackground(ColorF(1.0));

	const Font font(24);
	const Font font2(18);
	TextEditor editor;

	while (System::Update())
	{
		editor.update(font, font2, Vec2(10, 50));

		if (editor.isLocked())
		{
			Circle(400, 400, 80).draw(Palette::Red);
		}
	}
}
