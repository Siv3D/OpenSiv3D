
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();

	while (System::Update())
	{
		if (KeyA.down())
			Console << L"A";

		if (Key0.down())
			Console << L"0";
		
		if (KeyEnter.down())
			Console << L"Enter";
		
		if (KeySpace.down())
			Console << L"Space";
		
		if (KeyDown.down())
			Console << L"↓";
	}
}
