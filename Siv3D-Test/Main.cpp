
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (KeyR.down())
		{
			Window::Resize(1280, 720);
		}

		Rect(100, 50, 80).draw({Palette::Orange, Palette::Orange, Palette::White, Palette::White});

		Rect(200, 50, 80).draw(Arg::left = Palette::Orange, Arg::right = Palette::White);

		Rect(Arg::center(320, 240), 100, 40).rotated(System::FrameCount() * 1_deg).draw();

		Triangle(320, 240, 80).draw(Palette::Green);
	}
}
