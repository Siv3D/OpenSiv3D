# include <Siv3D.hpp> // OpenSiv3D v0.6
# include <emscripten.h>

# ifdef SIV3D_ENABLE_TEST

SIV3D_SET(EngineOption::Renderer::Headless)

void Siv3DTest();

void Main()
{
	Siv3DTest();
}

# else

SIV3D_SET(EngineOption::Renderer::WebGL2)

void RunMainLoop(void* arg)
{
	static_cast<const std::function<void()>*>(arg)->operator()();
}

void SetMainLoop(std::function<void()> mainLoop)
{
	emscripten_set_main_loop_arg(RunMainLoop, reinterpret_cast<void*>(&mainLoop), 0, 1);
}

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
	Scene::SetResizeMode(ResizeMode::Keep);
	Window::SetStyle(WindowStyle::Sizable);
	Window::Resize(1280, 720);

	SetMainLoop([&]() 
	{
		System::Update();

		for (auto i : step(20))
		{
			Rect{ Point{ 100, 100 } *i, 100 }.draw();
		}

		for (auto i : step(20))
		{
			Rect{ Cursor::Pos().movedBy(0 + i * 20, 0), 20, 400 }
				.draw(HSV{ i * 10.0, 0.5, 0.9 });
		}

		Rect{ Cursor::Pos(), 40 }.draw(Palette::Orange);
	});
}

# endif
