# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.4, 0.8, 0.6));

	while (System::Update())
	{
		Circle(200, 200, 80).drawShadow(Vec2(2, 2), 12, 4).draw();
	}
}
