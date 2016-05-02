
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;

static constexpr char hexTable[2][16] =
{
	{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' },
	{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' }
};

void Main()
{
	//constexpr char k = hexTable[false][9];

	//const char* table = hexTable[0];

	Log(CharacterSet::PercentEncode(L"ウィキペディア", false));
	
	RunTest();
}

/*
Pad
*/