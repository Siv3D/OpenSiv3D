
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	const Polygon poly = RoundRect(0, 0, 8, 4, 1).asPolygon();

	while (System::Update())
	{
		Transformer2D tr(Mat3x2::Scale(40));

		poly.draw();
	}
}
