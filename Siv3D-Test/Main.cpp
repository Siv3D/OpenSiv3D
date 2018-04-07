
# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);

	NavMesh navMesh;

	Polygon polygon;

	Vec3 start(100, 0, 100), end(300, 0, 300);

	LineString path;

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
			const Circle shape(Arg::center(Cursor::Pos()), 30);

			shape.drawFrame(2, Palette::Skyblue);

			if (MouseL.pressed())
			{
				dirty |= polygon.append(shape.asPolygon());
			}
		}

		if (KeyS.down())
		{
			++shapeIndex %= 3;
		}

		if (KeyG.down())
		{
			polygon = polygon.simplified(2.0);

			const Array<Float3> vertices = polygon.vertices().map([](auto v) { return Float3(v.x, 0.0, v.y); });

			const Array<uint16> indices = polygon.indices().map([](auto i) { return static_cast<uint16>(i); });

			if (navMesh.build(vertices, indices))
			{
				path = navMesh.query(start, end).map([](auto v) { return Vec2(v.x, v.z); });

				dirty = false;
			}
		}

		if (MouseM.down())
		{
			start.set(Cursor::Pos().x, 0, Cursor::Pos().y);

			path = navMesh.query(start, end).map([](auto v) { return Vec2(v.x, v.z); });
		}

		if (MouseR.pressed())
		{
			end.set(Cursor::Pos().x, 0, Cursor::Pos().y);

			path = navMesh.query(start, end).map([](auto v) { return Vec2(v.x, v.z); });
		}

		path.draw(10, Palette::Red);

		Circle(start.xz(), 16).draw(Palette::Red);

		Circle(end.xz(), 16).draw(Palette::Red);
	}
}
