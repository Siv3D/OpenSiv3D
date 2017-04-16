
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		Window::SetTitle(Profiler::FPS());

		if (KeyR.down())
		{
			Window::Resize(1280, 720);
		}
		
		for (auto p : step({10,10}))
		{
			Rect(p*20,18).draw(HSV(10*(p.x+p.y)));
		}

		Rect(100, 50, 80).draw({Palette::Orange, Palette::Orange, Palette::White, Palette::White});

		Rect(200, 50, 80).draw(Arg::left = Palette::Orange, Arg::right = Palette::White);

		Rect(Arg::center(320, 240), 160, 40).rotated(System::FrameCount() * 1_deg).draw(Palette::Seagreen);

		Triangle(Window::Center(), 80).draw(Palette::Orange);
		
		Rect(80, 160, 200).draw(Color(255, 127));

		Rect(300, 300, 200, 100).drawFrame(4);
	}
}
