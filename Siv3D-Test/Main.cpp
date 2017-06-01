# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.8));

	const Font font(50);

	int32 count = 0;
	
	while (System::Update())
	{
		//font(count).drawAt(Window::Center(), Palette::Yellow);

		//font(Cursor::Pos()).draw(20, 400);
		
		//Circle(Cursor::Pos(), 60).draw(ColorF(1, 0, 0, 0.5));
		
		if(MouseL.down())
		{
			++count;
		}
		
		//Window::SetTitle(MouseL.pressed());

		if (Key1.down())
			Cursor::SetStyle(CursorStyle::Arrow);
		if (Key2.down())
			Cursor::SetStyle(CursorStyle::IBeam);
		if (Key3.down())
			Cursor::SetStyle(CursorStyle::Cross);
		if (Key4.down())
			Cursor::SetStyle(CursorStyle::Hand);
		if (Key5.down())
			Cursor::SetStyle(CursorStyle::NotAllowed);
		if (Key6.down())
			Cursor::SetStyle(CursorStyle::ResizeUpDown);
		if (Key7.down())
			Cursor::SetStyle(CursorStyle::ResizeLeftRight);
		if (Key8.down())
			Cursor::SetStyle(CursorStyle::Hidden);
	}
}
