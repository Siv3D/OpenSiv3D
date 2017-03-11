
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.5, 0.5, 1.0));
	}
}
