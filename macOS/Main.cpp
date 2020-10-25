
# include <Siv3D.hpp>
SIV3D_SET(EngineOption::Renderer::Metal)

void Siv3DTest();

void Main()
{
	//Siv3DTest();
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
	//Scene::SetTextureFilter(TextureFilter::Nearest);
	//Scene::SetResizeMode(ResizeMode::Keep);
	//Scene::Resize(200, 200);
	//Window::Resize(800, 800);
	//LicenseManager::ShowInBrowser();
	//System::LaunchBrowser(U"test.html");
	//System::LaunchBrowser(U"https://siv3d.github.io/");
	//Window::SetStyle(WindowStyle::Sizable);
	//Scene::SetResizeMode(ResizeMode::Actual);
	
	while (System::Update())
	{
		for (auto i : step(16))
		{
			Rect(i*100, i * 100, 100).draw();
		}
		
		RectF(3.5, 3.5, 3).draw(ColorF(0.0));
		
		RectF(8, 3, 0.5).draw(ColorF(0.0));
		
		for (auto i : step(20))
		{
			Rect(Cursor::Pos().movedBy(0 + i * 20, 0), 20, 400)
				.draw(HSV(i * 10, 0.5, 0.9));
		}
	}
}
