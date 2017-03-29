
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.2));
	}
}
