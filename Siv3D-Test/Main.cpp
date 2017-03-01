
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();

	while (System::Update())
	{
		if (KeyO.down())
		{
			System::OepnLicense();
		}
	}
}
