
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	while (System::Update())
	{
		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.2));
	}
}
