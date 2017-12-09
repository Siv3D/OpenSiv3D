
# include <Siv3D.hpp>
# include "Test/Test.hpp"

void Main()
{
	const Font font(30);

	while (System::Update())
	{
		Print << System::FrameCount();

		font(U"Siv3D").draw();
	}
}
