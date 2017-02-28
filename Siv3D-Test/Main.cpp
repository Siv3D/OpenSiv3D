
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();

	Array<int> v = { 10,20,30 };

	v.push_front(5);

	v.push_front(6);
	
	v.pop_front();

	Log << v;

	while (System::Update())
	{
		
	}
}
