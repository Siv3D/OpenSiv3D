
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;
using namespace s3d::literals;

void Main()
{
	Log(Range(0, 1)
		.filter(Odd())
		.join(L", ", L"[", L"]"));

	/*
	take
	take_while
	reduce

	all
	any
	none
	take_while

	Range(0, INF, 2);

	Number
	String & &&

	Pad
	*/
}


