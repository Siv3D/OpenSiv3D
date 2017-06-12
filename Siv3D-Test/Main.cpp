# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.3, 0.9, 0.4));

	const Font font(40);
	
	while (System::Update())
	{
		font(L"Siv3D: {}"_fmt(System::FrameCount())).draw();

		Circle(Cursor::Pos(), 200).draw(Palette::Orange);

		if (KeyP.down())
		{
			ScreenCapture::SaveCurrentFrame();
		}

		if (Key1.down())
		{
			Window::Resize(800, 600);
		}

		if (Key2.down())
		{
			Window::Resize(1280, 720);
		}

		if (Key3.down())
		{
			Window::Resize(1920, 1080);
		}
	}
}
