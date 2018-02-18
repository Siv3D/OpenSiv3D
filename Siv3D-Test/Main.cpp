
# include <Siv3D.hpp>

void Main()
{
	auto polygon = Shape2D::Star(200, Vec2(0, 0), 0).asPolygon();

	polygon.addHole(Rect(Arg::center(0,0),70).asPolygon().vertices().map([](Float2 p) { return Vec2(p); }).reversed());

	polygon = polygon.calculateRoundBuffer(8);

	while (System::Update())
	{
		polygon.draw(Cursor::Pos());

		polygon.drawWireframe(Cursor::Pos(), 1, Palette::Blue);
	}
}