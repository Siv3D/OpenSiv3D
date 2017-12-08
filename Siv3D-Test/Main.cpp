
# include <Siv3D.hpp>
# include "Test/Test.hpp"

void Main()
{
	Graphics::SetBackground(ColorF(0.3, 0.7, 1.0));

	while (System::Update())
	{
		Circle(Cursor::Pos(), 50).draw();
	}
}
