
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

void Main()
{
	Scene::SetBackground(ColorF(0.96, 0.98, 1.0));
	Array<Vec2> points;

	while (System::Update())
	{
		if (MouseR.down())
		{
			points.clear();
		}

		ClearPrint();
		Print << Geometry2D::IsClockwise(points);

		if (MouseL.down())
		{
			points << Cursor::Pos();
		}

		for (const auto& point : points)
		{
			Circle(point, 10).draw(Palette::Orange);
		}

		if (points.size() > 2)
		{
			if (Geometry2D::IsClockwise(points))
			{
				for (size_t i = 0; i < points.size(); ++i)
				{
					Line(points[i], points[(i + 1) % points.size()])
						.stretched(-10)
						.drawArrow(3, Vec2::All(20), ColorF(0.25));
				}
			}
			else
			{
				for (size_t i = 0; i < points.size(); ++i)
				{
					Line(points[i], points[(i + 1) % points.size()])
						.reversed()
						.stretched(-10)
						.drawArrow(3, Vec2::All(20), ColorF(0.25));
				}
			}
		}

		//LineString(points).draw(2);
	}
}
