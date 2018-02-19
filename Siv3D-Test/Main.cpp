# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	P2World world;
	Array<P2Body> bodies;
	bodies << world.createLine(Vec2(0, 0), Line(-4, -0.5, 4, 0), none, none, P2BodyType::Static);
	bodies << world.createLineString(Vec2(0, 0), { Vec2(-6, 0), Vec2(-6, 2), Vec2(6, 2), Vec2(6, -2) }, none, none, P2BodyType::Static);
	Camera2D camera(Vec2(0, 0), 20);

	while (System::Update())
	{
		world.update();
		camera.update();

		auto t = camera.createTransformer();

		if (MouseL.down())
		{
			bodies << world.createCircle(Cursor::PosF(), 0.5);
		}

		for (const auto& body : bodies)
		{
			body.draw(HSV(body.id() * 30.0, 0.5, 1.0));
		}

		camera.draw(Palette::Orange);
	}
}