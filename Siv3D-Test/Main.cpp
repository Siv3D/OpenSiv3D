
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;
using namespace s3d::literals;

void Main()
{
	// 0 ~ 9 をログ出力
	Iota(10).each(Log<int>);

	// 1 + 2 + 3 + ... + 100
	Log(Iota(1, 101).reduce1(std::plus<>()));

	// 100!
	Log(Iota(1, 101).reduce1(std::multiplies<BigInt>()));
}
