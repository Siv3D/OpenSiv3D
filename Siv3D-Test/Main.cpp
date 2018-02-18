
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		Shape2D::Star(200, Vec2(0,0), 0).asPolygon().drawFrame(Cursor::Pos(), 6);
	}
}