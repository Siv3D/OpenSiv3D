
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;
using namespace s3d::literals;



void Main()
{
	size_t x = 0;

	constexpr bool k = InRange(0, 100)(20);

	{
		RDTSC t;
		x = Range(0, 1000000)
			.filter([](auto n) { return n%2!=0; })
			.count();
	}

	Log(x);

	{
		RDTSC t;
		x = Range(0, 1000000)
			.filter(Odd())
			.count();
	}

	Log(x);
	//Log(Range(0, 100)
	//	.filter([](auto n) { return n % 2 == 0; })
	//	.count());

	//Log(Range(0, 100)
	//	.filter([](auto n) { return n < 1000; })
	//	.reduce(std::plus<>(), 0));

	//Log(Range(0, 100)
	//	.filter([](auto n) {return n % 2 == 0; })
	//	.map([](auto n) { return n * 0.1; })
	//	.take(20).join(L", "));

	//const auto v = Range("1000000000000000000000000000000"_big,
	//					 "2000000000000000000000000000000"_big)
	//					.filter([](auto n) {return n % 33333 == 0; })
	//					.map([](auto n) { return n /= 345; })
	//					.take(20);

	//Log(v);
	/*
	filter
	asArray()
	include
	include_if
	join
	map
	all
	any
	none

	Number
	String & &&

	Pad
	*/
}


