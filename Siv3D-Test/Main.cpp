# include <Siv3D.hpp> //OpenSiv3D v0.1.5

void Main()
{
	while (System::Update())
	{
		const Circle circle(Cursor::Pos(), 50);
		const Bezier3 bezier(Vec2(100, 400), Vec2(300, 400), Vec2(300, 100), Vec2(500, 100));

		const auto points = circle.intersectsAt(bezier);
		bezier.draw(5, points ? Palette::Orange : Palette::White);
		circle.draw(points ? ColorF(Palette::Yellow, 0.8) : ColorF(1.0, 0.5));

		if (points)
		{
			for (const auto& point : points.value())
			{
				Circle(point, 8).draw(Palette::Red);
			}
		}
	}
}
