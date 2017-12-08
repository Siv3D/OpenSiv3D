
# include <Siv3D.hpp>
# include "Test/Test.hpp"

void Main()
{
	Graphics::SetBackground(ColorF(0.3, 0.7, 1.0));

	const Texture texture(U"example/windmill.png");
	
	while (System::Update())
	{
		texture.draw(10, 20);
		
		Circle(Cursor::Pos(), 50).draw();
	}
}
