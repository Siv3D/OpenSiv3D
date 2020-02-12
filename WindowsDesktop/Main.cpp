
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

struct Result
{
	bool firstValid = false;
	bool secondValid = false;
	bool hasHole = false;
};

Result Test(const Array<Vec2>& dataset)
{
	Result res;
	Array<Vec2> points;
	
	const size_t N = Random(0, 32);
	for (auto i : step(N))
	{
		points << dataset.choice();
	}

	Array<Array<Vec2>> holes;
	const size_t H = Random(0, 4);
	for (auto h : step(H))
	{
		Array<Vec2> hole;

		const size_t HN = Random(0, 8);
		for (auto i : step(HN))
		{
			hole << dataset.choice();
		}

		holes << hole;
	}

	if (Polygon::IsValid(points, holes))
	{
		res.firstValid = res.secondValid = true;
		res.hasHole = holes.size() > 0;
		return res;
	}

	const Array<Polygon> correct = Polygon::Correct(points, holes);

	if (correct)
	{
		res.secondValid = true;
		for (const auto& polygon : correct)
		{
			res.hasHole |= polygon.hasHoles();
		}
		return res;
	}

	return res;
}

void Main()
{
	/*
	Array<Vec2> dataset;

	for (auto p : step(Size(10, 10)))
	{
		for (auto i : step(8))
		{
			dataset << p + RandomVec2(0.1);
		}
	}

	const size_t N = 10;
	size_t count = 0;
	size_t first = 0, second = 0, hasHole = 0;

	while (System::Update())
	{
		for (auto i : step(N))
		{
			Result res = Test(dataset);
			first += res.firstValid;
			second += res.secondValid;
			hasHole += res.hasHole;
		}
		count += N;

		if (count % 100 == 0)
		{
			Console << U"{}({}/{})({})"_fmt(ThousandsSeparate(count), first, second, hasHole);
		}
	}
	*/
	Window::Resize(1280, 720);

	const Font font(20, Typeface::Bold);

	Array<Vec2> points;
	Array<Polygon> solvedPolygons;

	while (System::Update())
	{
		if (MouseL.down())
		{
			points << Cursor::Pos();
			solvedPolygons = Polygon::Correct(points, {});
		}
		else if (MouseR.down())
		{
			points.clear();
			solvedPolygons.clear();
		}

		for (auto [i, point] : Indexed(points))
		{
			Circle(point, 5).draw();
			Line(points[i], points[(i + 1) % points.size()])
				.drawArrow(2, Vec2(20, 20), Palette::Orange);
		}

		font(points).draw(Rect(20, 20, 600, 720));

		{
			Transformer2D trans(Mat3x2::Translate(640, 0));

			font(solvedPolygons).draw(Rect(20, 20, 600, 720));

			for (auto [i, solvedPolygon] : Indexed(solvedPolygons))
			{
				const HSV color(i * 40, 0.7, 1.0);
				solvedPolygon.draw(color);

				const auto& outer = solvedPolygon.outer();

				for (auto [k, point] : Indexed(outer))
				{
					const Vec2 begin = outer[k];
					const Vec2 end = outer[(k + 1) % outer.size()];
					const Vec2 v = (end - begin).normalized();
					const Vec2 c = (begin + end) / 2;
					const Vec2 oc = c + v.rotated(-90_deg) * 10;
					Line(oc - v * 20, oc + v * 20)
						.drawArrow(2, Vec2(10, 10), color);
				}
			}
		}
	}
}
