# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		for (auto p : step({ 80, 40 }))
		{
			Circle(p * 10, 20).draw();
		}

		Circle(Cursor::Pos(), 40).draw(ColorF(1, 0, 0, 0.5));
	}
}
