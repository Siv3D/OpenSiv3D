# include <Siv3D.hpp> // OpenSiv3D v0.1.7
# include <HamFramework.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	while (System::Update())
	{

		if (MouseL.down())
		{
			Window::SetTitle(L"My Game");
		}
	}
}