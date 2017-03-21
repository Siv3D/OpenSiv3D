
# include <Siv3D.hpp>

void Main()
{
	constexpr int s = sizeof(Circle);
	constexpr auto t1 = Circle(10, 50, 50).center;
	Log << t1;
	Log << t1.x;
	Log << t1.y;

	while (System::Update())
	{
		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.5, 0.5, 1.0));
	}
}
