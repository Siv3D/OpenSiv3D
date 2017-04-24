# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		Rect(20).draw();

		Rect(100, 100, 100).drawFrame(20, 0);

		Circle(Cursor::Pos(), 40).drawFrame(20, 0);
	}
}