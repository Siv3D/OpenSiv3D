# include <Siv3D.hpp> // OpenSiv3D v0.1.7

void Main()
{
	const Triangle triangle({ 40, 100 }, { 400, 20 }, { 200, 250 });

	Array<Vec2> points;

	for (auto i : step(2000))
	{
		points << RandomVec2(triangle);
	}

	while (System::Update())
	{
		triangle.draw(Color(100));

		for (const auto& point : points)
		{
			Circle(point, 1).draw();
		}
	}
}
