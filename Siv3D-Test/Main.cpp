# include <Siv3D.hpp> // OpenSiv3D v0.1.7

void Main()
{
	const Vec2 p1(0, 1);
	const Vec2 p2(1, 1);

	LineString lineString;

	for (double x = 0; x <= 1.0; x += 0.01)
		lineString.emplace_back(p1.lerp(p2, x).movedBy(0, 1.0*(pow(0.5 - x, 2.0) - 0.25)));

	while (System::Update())
	{
		const auto t = Transformer2D(Mat3x2::Scale(300));

		//描画されない
		lineString.draw(0.1);

		//描画される
		if(MouseL.pressed())
		for (int i = 0; i < int(lineString.size() - 1); i++)
			Line(lineString[i], lineString[i + 1]).draw(0.1);
	}
}