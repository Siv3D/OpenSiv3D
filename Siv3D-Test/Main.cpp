// OpenSiv3D v0.1.4-
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.6));
	const Texture texture(L"example/siv3d-kun.png");
	const RoundRect rect(30, 50, 100, 100, 25);
	Stopwatch s;

	while (System::Update())
	{
		if (MouseL.down())
		{
			s.restart();
		}

		if (s > 3.0s)
		{
			const double t = std::min((s.sF() - 3.0) * 3, 1.0);
			RectF(640, 480 * t).draw(Arg::top = ColorF(1, 0.8, 0, t), Arg::bottom = ColorF(0.9, 0.6, 0, t));
			RectF(640 * t, 20).draw(ColorF(0, t * 0.8));
		}

		if (s > 2.4s)
		{
			rect.drawShadow(Vec2(1, 2), 8, 1);
		}

		if (s > 0.6s)
		{
			rect.draw(Palette::Skyblue);
		}

		if (s > 1.2s)
		{
			rect(texture(90, 5, 110)).draw();
		}

		if (s > 1.8s)
		{
			rect.drawFrame(6, 0, AlphaF(0.1)).drawFrame(4, 0, AlphaF(0.2)).drawFrame(2, 0, AlphaF(0.4));
		}
	}
}