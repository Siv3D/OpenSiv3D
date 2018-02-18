
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		Shape2D::Star(200, Vec2(0,0), 0).asPolygon().rotateAt(Cursor::Pos(), System::FrameCount()*1_deg).drawWireframe(Cursor::Pos(), 6);
	}
}