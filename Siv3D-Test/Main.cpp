
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;

void Main()
{
	const auto v = Range(5'000'000, 1'000'000'000)
					.filter([](auto n) { return n % 3333 == 0; })
					.take(500)
					.map([](auto n) { return n / 123.4; });
	Log(v);
}


