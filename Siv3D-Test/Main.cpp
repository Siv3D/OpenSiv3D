
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;
using namespace s3d::literals;
using namespace std::chrono_literals;

void Main()
{
	Log(L"Hello, Siv3D!");

	// 0～100 の範囲
	Log(L"# Range(0, 100)");
	Log(Range(0, 100));

	// 0～100 の合計
	Log(L"# Range(0, 100).reduce1(Plus())");
	Log(Range(0, 100).reduce1(Plus()));

	// 0～100 のうち 20 未満の個数
	Log(L"# Range(0, 100).count_if(LessThan(20))");
	Log(Range(0, 100).count_if(LessThan(20)));

	// 0～10 の範囲の奇数
	Log(L"# Range(0, 10).filter(Odd())");
	Log(Range(0, 10).filter(Odd()));

	// 100 の階乗
	Log(L"# Range(1, 100).reduce1(Multiplies<BigInt>())");
	Log(Range(1, 100).reduce1(Multiplies<BigInt>()));

	// FizzBuzz
	Log(L"# FizzBuzz");
	Range(1, 20).map([](auto n) { return n % 15 == 0 ? L"FizzBuzz"
									   : n %  3 == 0 ? L"Fizz"
									   : n %  5 == 0 ? L"Buzz"
									   : Format(n); }).each(Log);
	// フィボナッチ数列
	Log(L"# Fibbonaci");
	BigInt a = 0, b = 1;
	Log(a, L'\n', b);
	Range(1, 100).map([&a, &b](auto) { a = std::exchange(b, a + b); return b; }).each(Log);
}
