# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		const Triangle triangle(100, 100, 300, 100, 150, 200);

		const auto triangle2 = Quad(100, 100, 300, 100, 150, 200, 100, 180).moveBy(Cursor::Pos());
		
		triangle.draw();

		triangle2.draw(triangle.intersects(triangle2) ? Palette::Red : Palette::Yellow);
	}
}
