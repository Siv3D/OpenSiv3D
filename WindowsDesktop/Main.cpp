
# define SIV3D_WINDOWS_HIGH_DPI
# include <Siv3D.hpp>

void Main()
{
	Window::SetFullscreen(true, DisplayResolution::HD_1366x768);
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	const Font font(30);

	while (System::Update())
	{
		RectF(Periodic::Sine0_1(2s) * 1300, 400, 50, 50).draw();

		font(Profiler::FPS()).draw(20, 20);

		Circle(Cursor::Pos(), 30).draw(ColorF(1.0, 0.0, 0.0, 0.5));
	}
}
