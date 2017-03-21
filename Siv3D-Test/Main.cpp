
# include <Siv3D.hpp>

void Main()
{
	// 指定した線分を直径とする円
	Log << Circle(Line(0, 0, 10, 0));

	// 指定した 2 点を結ぶ線分を直径とする円
	Log << Circle(Vec2(0, 4), Vec2(3, 5));

	// 指定した 3 点を通る円
	Log << Circle(Vec2(0, 4), Vec2(3, 5), Vec2(10, 8));

	// 第 1 引数の座標が中心で、第 2 引数の座標を通る円
	Log << Circle(Arg::center(5, 5), Vec2(10, 10));

	while (System::Update())
	{
		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.5, 0.5, 1.0));
	}
}

