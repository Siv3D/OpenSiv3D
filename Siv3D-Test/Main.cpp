
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();

	Log << FileSystem::SpecialFolderPath(SpecialFolder::LocalAppData);
	
	while (System::Update())
	{

	}
}
