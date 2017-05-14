
# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);

	Graphics::SetBackground(ColorF(1.0, 0.8, 0.3));

	int32 x0 = 300;

	double thickness = 24;

	while (System::Update())
	{
		const Vec2 v = Circular(Arg::r = 120, Arg::theta = Time::GetMillisec() * 0.001) + Vec2(860, 160);

		RectF(x0, 0, v.x - x0, 720).draw(Palette::White);

		thickness = sin(Time::GetMillisec() * 0.000212) * 15 + 17;

		Line(x0, 50, v.x, v.y).draw(thickness, Palette::Black);

		Line(x0, 150, v.x, v.y + 100).draw(LineStyle::NoCap, thickness, Palette::Black);

		Line(x0, 250, v.x, v.y + 200).draw(LineStyle::RoundCap, thickness, Palette::Black);

		Line(x0, 350, v.x, v.y + 300).draw(LineStyle::SquareCapDot, thickness, Palette::Black);

		Line(x0, 450, v.x, v.y + 400).draw(LineStyle::RoundCapDot, thickness, Palette::Black);
	}
}
