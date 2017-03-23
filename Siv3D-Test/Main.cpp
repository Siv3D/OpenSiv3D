
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (KeyU.down())
		{
			Window::SetPos(Point(200, 200));
		}
		
		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.5, 0.5, 1.0));
	}
}

