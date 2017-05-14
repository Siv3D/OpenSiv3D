
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Palette::White);

	while (System::Update())
	{
		Window::SetTitle(Profiler::FPS(), L"FPS");

		Line(100, 20, 100, 420).draw(Palette::Gray);

		Line(500, 20, 500, 420).draw(Palette::Gray);

		Line(100, 100, 500, 100).draw(8, Palette::Red);
	}
}
