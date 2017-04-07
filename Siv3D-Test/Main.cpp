
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	int32 frame = 0;
	
	while (System::Update())
	{
		Window::SetTitle(frame++);
	}
}
