
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	while (System::Update())
	{
		Window::SetTitle(System::DeltaTime());
	}
}
