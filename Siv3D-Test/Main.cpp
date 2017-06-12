# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.3, 0.9, 0.4));
	
	while (System::Update())
	{
		for (auto i : step(16))
		{
			Circle(20 +40 * i, 100, i * 0.5).draw();

			Circle(20 + 40 * i, 200, (i+16)*0.5).draw();

			Circle(Cursor::Pos(), 100).draw();
		}
	}
}
