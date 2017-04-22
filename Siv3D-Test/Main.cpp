# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		for (auto i : step(12))
		{
			Rect(10 + i * 40, 20, 30).draw(HSV(i * 30));
		}

		Rect(Arg::center(Window::Center()), 200, 20).rotated(System::FrameCount() * 0.01).draw();

		Circle(Cursor::Pos(), 40).draw(ColorF(1.0, 0.0, 0.2, 0.6));
	}
}
