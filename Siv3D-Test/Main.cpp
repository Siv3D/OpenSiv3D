# include <Siv3D.hpp> // OpenSiv3D v0.1.5
# include <HamFramework.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.8, 0.9, 1.0));

	const Font font(50), fontSmall(20);
	const TextBox textBox(fontSmall, Vec2(40, 40), 200);

	const Array<Vec2> outer = Shape2D::Hexagon(100, Vec2(500, 200)).vertices().map([](Float2 v) { return Vec2(v); });
	const Array<Vec2> hole = Shape2D::Hexagon(40, Vec2(500, 180)).vertices().reversed().map([](Float2 v) { return Vec2(v); });
	const Polygon polygon(outer, { hole });
	const Circle circle(220, 240, 120);

	Camera2D camera;

	while (System::Update())
	{
		camera.update();
		auto t = camera.createTransformer();

		textBox.update();

		font(L"Siv3D v0.1.5!🐣").draw(100, 400, ColorF(0.4));

		const Rect rect(Cursor::Pos(), 200, 100);

		circle.draw(Palette::Skyblue);

		polygon.draw(Palette::Seagreen);

		rect.draw(ColorF(Palette::Orange, 0.5));

		if (const auto intersections = rect.intersectsAt(circle))
		{
			for (const auto& point : intersections.value())
			{
				Circle(point, 10).draw(Palette::Red);
			}
		}

		textBox.draw();
		camera.draw(Palette::Pink);
	}
}
