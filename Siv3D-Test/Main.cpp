
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;
using namespace s3d::literals;

void Main()
{
	Log(Range(1, 100)
		.filter(LessThanEqual(10))
		.map([](auto n) {return n*0.1; })
		.reduce1(std::plus<>()));

	/*
	reduce

	DIGITS
	Number
	String & &&

	Pad
	*/
}


