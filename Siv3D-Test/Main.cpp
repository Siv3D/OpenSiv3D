# include <Siv3D.hpp> // OpenSiv3D v0.1.7

[[nodiscard]] int GetFive()
{
	return 5;
}

void Main()
{
	Point pos(200, 400);

	GetFive();

	while (System::Update())
	{
		pos.movedBy(10, 20);

		Point(20, 20).movedBy(2, 2);

		Point::One();
	}
}
