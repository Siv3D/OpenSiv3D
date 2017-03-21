
# include <Siv3D.hpp>

void Main()
{
	constexpr auto v = Triangle(0, 0, 10, 0, 0, 10).p2;
	Log << v;

	while (System::Update())
	{
		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.5, 0.5, 1.0));
	}
}

