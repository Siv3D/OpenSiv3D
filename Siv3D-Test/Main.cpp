# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.2, 0.5, 0.3));

	const Font font(50);

	int32 count = 0;
	
	while (System::Update())
	{
		font(count).drawAt(Window::Center(), Palette::Yellow);

		font(Cursor::Pos()).draw(20, 400);
		
		Circle(Cursor::Pos(), 60).draw(ColorF(1, 0, 0, 0.5));
		
		if(MouseL.down())
		{
			++count;
		}
		
		Window::SetTitle(MouseL.pressed());
	}
}
