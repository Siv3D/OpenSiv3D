# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.8));

	const Polygon star1(Shape2D::Star(100, Window::Center().movedBy(-160,0)));
	const Polygon star2(Shape2D::Star(100, Window::Center().movedBy(160, 0)));

	double distance = -5;

	while (System::Update())
	{
		distance += Mouse::Wheel();

		ClearPrint();

		if (distance > 0)
		{
			star1.calculateRoundBuffer(distance).draw(ColorF(0.0, 0.5, 1.0));
		}

		star1.draw(ColorF(1.0, 0.9, 0.0));

		if (distance < 0)
		{
			star1.calculateRoundBuffer(distance).draw(ColorF(0.0, 0.5, 1.0));
		}

		if (distance > 0)
		{
			star2.calculateBuffer(distance).draw(ColorF(0.0, 0.5, 1.0));
		}

		star2.draw(ColorF(1.0, 0.9, 0.0));

		if (distance < 0)
		{
			star2.calculateBuffer(distance).draw(ColorF(0.0, 0.5, 1.0));
		}
	}
}