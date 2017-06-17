# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	ScalableWindow::SetBaseSize(640, 480);

	Window::Resize(1000, 800);

	Graphics::SetBackground(Palette::White);

	const int32 dotSize = 40;

	Grid<int32> dots(Window::BaseWidth() / dotSize, Window::BaseHeight() / dotSize);

	while (System::Update())
	{
		const auto transformer = ScalableWindow::CreateTransformer();

		for (auto p : step({ dots.size() }))
		{
			const Rect rect(p * dotSize, dotSize, dotSize);

			if (rect.leftClicked())
			{
				++dots[p.y][p.x] %= 4;
			}

			const Color color(240 - dots[p.y][p.x] * 70);

			rect.stretched(-1).draw(color);
		}

		ScalableWindow::DrawBlackBars(HSV(40, 0.2, 0.9));
	}
}