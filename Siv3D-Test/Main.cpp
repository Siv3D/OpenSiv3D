
# include <Siv3D.hpp>

void Main()
{
	Array v = { 1.1, 2.2, 3.3, 4.4 };

	Grid grid = {
		{ 1,2,3,4 },
		{ 5,6,7,8 },
		{ 9,0,1,2 },
	};

	Optional opt = 123;
	
	Print << v;
	Print << grid;
	Print << opt;
	
	while (System::Update())
	{

	}
}
