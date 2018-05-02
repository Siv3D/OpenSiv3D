
# include <Siv3D.hpp>
# include <HamFramework.hpp>

MultiPolygon MakePolygons(const Font& font, const String& text)
{
	Image image(1200, 180, Color(0, 0));

	font(text).overwrite(image, 0, 0, Palette::White);

	return image.alphaToPolygons().simplified(1).movedBy(-400, -500).scaled(0.025);
}

void Main()
{
	Window::Resize(1280, 720);
	Graphics::SetBackground(ColorF(0.94, 0.91, 0.86));

	P2World world;
	const P2Body line = world.createLine(Vec2(0, 0), Line(-16, 0, 16, 0), P2Material(1, 0.1, 1.0), none, P2BodyType::Static);
	Array<P2Body> bodies;

	Camera2D camera(Vec2(0, -5), 38);
	camera.enableKeyControl(false);

	const Font font(100, Typeface::Bold);
	String text;
	int32 generation = 0;
	HashTable<P2BodyID, int32> table;

	while (System::Update())
	{
		TextInput::UpdateText(text);

		world.update(System::DeltaTime(0.05), 12*8, 4*8);

		camera.update();

		auto t = camera.createTransformer();

		for (const auto& body : bodies)
		{
			body.draw(HSV(table[body.id()] * 45 + 30, 0.75, 0.85));

			//body.drawWireframe(1, ColorF(0.25));
		}

		line.draw(Palette::Green);

		{
			Transformer2D trans(Mat3x2::Scale(0.025));

			font(text + TextInput::GetEditingText()).draw(-400, -500, ColorF(0.5));
		}

		if (text.includes(U'\n'))
		{
			for (const auto& poly : MakePolygons(font, text))
			{
				const Vec2 centroid = poly.centroid();

				bodies << world.createPolygon(centroid, poly.movedBy(-centroid), P2Material(1, 0.0, 0.4));

				table[bodies.back().id()] = generation;
			}

			text.clear();

			++generation;
		}

		if (KeyDelete.down())
		{
			bodies.clear();
		}

		camera.draw(Palette::Orange);
	}
}
