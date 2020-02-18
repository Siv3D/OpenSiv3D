# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF(0.99));
	const Rect rect(50, 50, Scene::Size() - Size(100, 100));

	Subdivision2D subdiv(rect);
	Array<Triangle> triangles;
	Array<VoronoiFacet> facets;
	Array<Polygon> facetPolygons;

	while (System::Update())
	{
		const Vec2 pos = Cursor::Pos();

		if (rect.leftClicked())
		{
			subdiv.addPoint(pos);
			subdiv.calculateTriangles(triangles);
			subdiv.calculateVoronoiFacets(facets);
			facetPolygons = facets.map([rect = rect.asPolygon()](const VoronoiFacet& f)
			{
				return Geometry2D::And(Polygon(f.points), rect).front();
			});
		}

		rect.draw(ColorF(0.75));

		for (auto [i, facetPolygon] : Indexed(facetPolygons))
		{
			facetPolygon.draw(HSV(i * 25.0, 0.65, 0.8)).drawFrame(3, ColorF(0.25));
		}

		for (const auto& triangle : triangles)
		{
			triangle.drawFrame(2.5, ColorF(0.9));
		}

		for (const auto& facet : facets)
		{
			Circle(facet.center, 6).drawFrame(5).draw(ColorF(0.25));
		}

		if (const auto nearestVertexID = subdiv.findNearest(pos))
		{
			const Vec2 nearestVertex = subdiv.getVertex(nearestVertexID.value());
			Line(pos, nearestVertex).draw(LineStyle::RoundDot, 5);
			Circle(nearestVertex, 16).drawFrame(3.5);
		}
	}
}
