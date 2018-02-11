# include <Siv3D.hpp>

void Main()
{
	const LineString line
	{
		Vec2(50, 100), Vec2(600, 100),
		Vec2(50, 200), Vec2(600, 200),
		Vec2(50, 300), Vec2(600, 300),
		Vec2(50, 400)
	};

	const Polygon roundLine = line.calculateBuffer(15);

	while (System::Update())
	{
		if (Periodic::Square0_1(2.0s))
		{
			line.draw(30, Palette::Yellow);
		}
		else
		{
			roundLine.draw(Palette::Orange);
		}
	}
}