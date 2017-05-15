
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		const double offset = Time::GetMillisec() * 0.005;

		LineString{ {100, 100}, {500, 100}, {500, 400}, {100, 400} }
			.draw(LineStyle::SquareDot(offset * 2), 8, Palette::White, true);

		Line(150, 350, 450, 150)
			.draw(LineStyle::RoundDot(offset), 10, { HSV(20), HSV(60) });
	}
}
