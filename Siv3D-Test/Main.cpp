
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();

	while (System::Update())
	{
		Array<int>().push_back(2);
	}
}
