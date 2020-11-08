
# include <Siv3D.hpp> // OpenSiv3D v0.6
//*
SIV3D_SET(EngineOption::Renderer::Headless) // 非グラフィックモード
//*/

void Siv3DTest();

void Main()
{
	Siv3DTest();

/*
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
	Scene::SetResizeMode(ResizeMode::Keep);
	Window::SetStyle(WindowStyle::Sizable);
	Window::Resize(1280, 720);

	while (System::Update())
	{
		for (auto i : step(20))
		{
			Rect(Point{ 100, 100 } *i, 100).draw();
		}

		for (auto i : step(20))
		{
			Rect(Cursor::Pos().movedBy(0 + i * 20, 0), 20, 400)
				.draw(HSV(i * 10, 0.5, 0.9));
		}

		Rect(Cursor::Pos(), 40).draw(Palette::Orange);
	}
//*/
}
