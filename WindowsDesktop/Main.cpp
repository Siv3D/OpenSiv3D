

# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	while (System::Update())
	{
		Line(Vec2(100, 100), Arg::angle = 45_deg, 100)
			.draw(LineStyle::RoundCap, 6);

		Line(Vec2(100, 100), Arg::direction = Vec2(0, 200))
			.draw(LineStyle::RoundCap, 6, Palette::Orange);
	}
}






