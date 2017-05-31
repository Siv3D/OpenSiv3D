# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.2, 0.5, 0.3));

	const Font font(50);

	while (System::Update())
	{
		font(L"Hello, Siv3D!🐣").drawAt(Window::Center(), Palette::Yellow);

		font(Cursor::Pos()).draw(20, 400);
		
		Circle(Cursor::Pos(), 60).draw(ColorF(1, 0, 0, 0.5));
	}
}
