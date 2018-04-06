
# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);

	NavMesh navMesh;

	Vec2 start(100, 100), end(300, 300);

	Array<Vec3> paths;

	Polygon polygon;

	bool dirty = true;
	int32 shapeIndex = 0;

	while (System::Update())
	{
		polygon.draw(dirty ? Palette::Gray : Palette::Yellow);

		polygon.drawWireframe(1.0, Palette::Gray);

		if (shapeIndex == 0)
		{
			const Rect shape(Arg::center(Cursor::Pos()), 80);

			shape.drawFrame(2, Palette::Skyblue);

			if (MouseL.down())
			{
				dirty |= polygon.append(shape.asPolygon());
			}
		}
		else if (shapeIndex == 1)
		{
			const Shape2D shape = Shape2D::Plus(60, 40, Cursor::Pos());

			shape.drawFrame(2, Palette::Skyblue);

			if (MouseL.down())
			{
				dirty |= polygon.append(shape.asPolygon());
			}
		}
		else if (shapeIndex == 2)
		{
			const Shape2D shape = Shape2D::Star(60, Cursor::Pos());

			shape.drawFrame(2, Palette::Skyblue);

			if (MouseL.down())
			{
				dirty |= polygon.append(shape.asPolygon());
			}
		}
		else if (shapeIndex == 3)
		{
			const Circle shape(Arg::center(Cursor::Pos()), 30);

			shape.drawFrame(2, Palette::Skyblue);

			if (MouseL.pressed())
			{
				dirty |= polygon.append(shape.asPolygon());
			}
		}

		if (KeyS.down())
		{
			++shapeIndex %= 5;
		}

		if (KeyG.down())
		{
			polygon = polygon.simplified(2.0);

			Array<Triangle3D> triangles;

			for (size_t i = 0; i < polygon.num_triangles(); ++i)
			{
				const Triangle t = polygon.triangle(i);

				triangles.emplace_back(Vec3(t.p0.x, 0.0, t.p0.y), Vec3(t.p1.x, 0.0, t.p1.y), Vec3(t.p2.x, 0.0, t.p2.y));
			}

			navMesh.build(triangles);

			paths = navMesh.query(Vec3(start.x, 0, start.y), Vec3(end.x, 0, end.y));

			dirty = false;
		}

		if (MouseM.down())
		{
			start = Cursor::Pos();
			paths = navMesh.query(Vec3(start.x, 0, start.y), Vec3(end.x, 0, end.y));
		}

		if (MouseR.down())
		{
			end = Cursor::Pos();
			paths = navMesh.query(Vec3(start.x, 0, start.y), Vec3(end.x, 0, end.y));
		}

		if (paths)
		{
			for (size_t i = 0; i < paths.size() - 1; ++i)
			{
				const Float3 a = paths[i];
				const Float3 b = paths[i + 1];

				Line(a.x, a.z, b.x, b.z).draw(10, Palette::Red);
			}
		}

		Circle(start, 16).draw(Palette::Red);

		Circle(end, 16).draw(Palette::Red);
	}
}
