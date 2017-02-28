
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();

	while (System::Update())
	{
		if (Key0.down())
		{
			Log << L"Hi";
		}
	}
}
