# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
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

	while (System::Update())
	{
		poly.draw(poly.intersects(polygon) ? Palette::Gold : Palette::Yellow);

		polygon.moveBy(0.3, 0.1);

		polygon.draw(polygon.mouseOver() ? Palette::Red: Palette::Yellow);
	}
}
