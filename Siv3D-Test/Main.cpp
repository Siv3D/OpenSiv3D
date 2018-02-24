# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.1, 0.7, 1.0));
	P2World world;
	Array<P2Body> bodies;
	Array<Polygon> polys;
	Array<Texture> textures;
	HashTable<P2BodyID, size_t> table;
	size_t index = 0;
	Camera2D camera(Vec2(0, 0), 20);
	const P2Body line = world.createLine(Vec2(0, 0), Line(-12, 0, 12, 0), P2Material(1, 0.1, 1.0), none, P2BodyType::Static);

	for (const auto& animal : { U"🐘", U"🐧", U"🐐", U"🐤", U"🖐🏼" })
	{
		polys << ImageProcessing::FindExternalContour(Emoji::LoadImage(animal), true).moveBy(-68, -64).simplified(0.8).scale(0.04);
		textures << Texture(Emoji(animal), TextureDesc::Mipped);
	}
	Array<P2RevoluteJoint> joints;

	while (System::Update())
	{
		world.update();
		camera.update();
		auto t = camera.createTransformer();

		if (MouseL.down())
		{
			bodies << world.createPolygon(Cursor::PosF(), polys[index], P2Material(0.1, 0.0, 1.0));
			table.emplace(bodies.back().id(), std::exchange(index, Random(polys.size() - 2)));
		}

		if (MouseR.down())
		{
			index = polys.size() - 1;
			bodies << world.createPolygon(Cursor::PosF(), polys[index], P2Material(0.1, 0.0, 0.2));
			table.emplace(bodies.back().id(), std::exchange(index, Random(polys.size() - 2)));
			joints << world.createRevoluteJoint(line, bodies.back(), Cursor::PosF());
			joints.back().setMotorEnabled(true);
			joints.back().setMotorSpeed(90_deg);
			joints.back().setMaxMotorTorque(10000.0);
		}

		for (const auto& body : bodies)
		{
			textures[table[body.id()]].scaled(0.04).rotated(body.getAngle()).drawAt(body.getPos());
		}

		line.draw(Palette::Green);
		textures[index].scaled(0.04).drawAt(Cursor::PosF());
	}
}
