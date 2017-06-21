# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(1.0));

	const Array<Vec2> vs = {
		Vec2(100, 100), Vec2(200, 100), Vec2(200, 200), Vec2(100, 200)
	};

	const Array<Vec2> hole1 = {
		Vec2(150, 140), Vec2(140, 150), Vec2(160, 150),
	};

	const Array<Vec2> hole2 = {
		Vec2(150, 180), Vec2(140, 190), Vec2(160, 190),
	};

	const Triangle t1(Point(200, 200), 330);
	const Triangle t2(Point(200, 200), 140, Math::Pi);
	Polygon polygon({ t1.p0, t1.p1, t1.p2 }, { { t2.p2, t2.p1, t2.p0 } });

	Polygon poly(vs, { hole1, hole2 });

	/*
			poly.draw(poly.intersects(polygon) ? Palette::Gold : Palette::Yellow);

		polygon.moveBy(0.3, 0.1);

		polygon.draw(polygon.mouseOver() ? Palette::Red: Palette::Yellow);
	*/

	while (System::Update())
	{
		const Ellipse circle(320, 240, 150, 80);
		const Line line(50, 400, Cursor::Pos());
		const Rect rect(Cursor::Pos() + Point(40, 40), 300, 150);

		circle.draw(Palette::Skyblue);
		line.draw(Palette::Orange);
		rect.draw(ColorF(Palette::Orange, 0.5));

		if (const auto intersections = circle.intersectsAt(line))
		{
			for (const auto& pos : intersections.value())
			{
				Circle(pos, 6).draw(Palette::Red);
			}
		}

		if (const auto intersections = circle.intersectsAt(rect))
		{
			for (const auto& pos : intersections.value())
			{
				Circle(pos, 6).draw(Palette::Red);
			}
		}
	}
}
