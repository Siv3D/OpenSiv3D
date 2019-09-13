# include <Siv3D.hpp> // OpenSiv3D v0.4.1

void Main()
{
	const Array<Polygon> polygons =
	{
		Shape2D::Star(280, Vec2(400, 300)),
		Rect(Arg::center(400,300), 200).asPolygon(),
		Circle(400, 300, 280).asPolygon()
	};

	size_t polygonIndex = 0;

	while (System::Update())
	{
		if (MouseL.down())
		{
			++polygonIndex %= polygons.size();
		}

		const Rect rect(Arg::center = Cursor::Pos(), 120, 60);

		ScopedRenderStates2D rast(RasterizerState::SolidCullBack);
		{
			const Array<Polygon> results = Geometry2D::Subtract(polygons[polygonIndex], rect.asPolygon());

			for (auto[i, result] : Indexed(results))
			{
				result.draw(HSV(i * 60, 0.5));

				for (const auto& hole : result.inners())
				{
					for (size_t i : step(hole.size() - 1))
					{
						Line(hole[i], hole[i + 1]).drawArrow();
					}
				}
			}
		}

		//polygon.draw();
	}
}
