
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;
using namespace s3d::literals;

void Main()
{
	const auto v = Range("1000000000000000000000000000000"_big,
						 "2000000000000000000000000000000"_big)
						.filter([](auto n) {return n % 33333 == 0; })
						.map([](auto n) { return n /= 345; })
						.take(20);
	Log(v);
}


