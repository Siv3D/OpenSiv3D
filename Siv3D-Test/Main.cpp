
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(55, 111, 222));
	
	while (System::Update())
	{
		if (KeyR.down())
		{
			Window::Resize(1280, 720);
		}

		for (auto p : step({ 10, 10 }))
		{
			Rect(p * 40, 38).draw(HSV(10 * (p.x + p.y)));
		}

		Rect(Arg::center = Cursor::Pos(), 20).draw();
	}
}
