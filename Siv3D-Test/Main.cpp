
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;
using namespace s3d::literals;

void Main()
{
	Log(Range(0, 100)
		.take_while(LessThanEqual(40))
		.join(L", ", L"[", L"]"));

	/*
	take_while
	reduce

	DIGITS
	Number
	String & &&

	Pad
	*/
}


