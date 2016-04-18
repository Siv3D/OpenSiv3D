
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;

void Main()
{
	RunTest();
	
	Log(IsInfinity(Infinity<double>()));

	Log(IsInfinity(0));
}


/*
reduce

DIGITS
Number
String & &&

Pad
*/