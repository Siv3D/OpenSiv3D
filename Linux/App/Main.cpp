
# include <Siv3D.hpp>
SIV3D_SET(EngineOption::Renderer::Headless) // 非グラフィックモード

void Siv3DTest();

void Main()
{
	Siv3DTest();
/*
	//System::LaunchBrowser(U"https://siv3d.github.io/");
	//LicenseManager::ShowInBrowser();
	Window::SetStyle(WindowStyle::Sizable);

	while (System::Update())
	{
		Window::SetTitle(U"{} FPS | {} {}"_fmt(Profiler::FPS(), Cursor::Pos(), Cursor::ScreenPos()));

		for (auto i : step(20))
		{
			Rect(20 + i * 20, 20, 20, 400)
				.draw(HSV(i * 10, 0.5, 0.9));
		}

		Rect(Cursor::Pos(), 50).draw(ColorF(0.25));
	}
	*/
}
