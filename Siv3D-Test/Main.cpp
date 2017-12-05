
# include <Siv3D.hpp>
# include "Test/Test.hpp"

void Main()
{
	//Siv3D_RunTest();

	System::EnumActiveMonitors().each(Logger);

	while (System::Update())
	{

	}
}
