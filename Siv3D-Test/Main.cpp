
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();

	while (System::Update())
	{
		if ((KeyControl + KeyC).down())
		{
			Log << (KeyControl + KeyC);
		}
		
		if ((KeyCommand + KeyC).down())
		{
			Log << (KeyCommand + KeyC);
		}
	}
}
