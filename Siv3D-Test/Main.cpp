
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();

	Logger::RemoveLogOnExit();

	while (System::Update())
	{
		if (KeyO.down())
		{
			System::OepnLicenses();
		}
	}
}
