
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;
using namespace s3d::literals;

void Main()
{
	// 0 ~ 4 を出力
	Iota(5).each(Log<int>);

	// 1 + 2 + 3 + ... + 100
	Log(Iota(1, 101).reduce1(std::plus<>()));

	// 100 の階乗
	Log(Iota(1, 101).reduce1(std::multiplies<BigInt>()));

	// 100000000000000000000000000000000000000000000000001
	// +
	// 100000000000000000000000000000000000000000000000002
	// +
	// ...
	// +
	// 100000000000000000000000000000000000000000000000100
	Log(step(BigInt(L"100000000000000000000000000000000000000000000000001"), 100, 1).reduce1(std::plus<>()));
}
