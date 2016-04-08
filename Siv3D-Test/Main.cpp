
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;

void Main()
{
	// Fibbonaci (0, 1, 1, 2, 3, 5, .., 573147844013817084101)
	BigInt a = 0, b = 1, t;
	Log(L"0\n1\n");
	Range(1, 100).map([&](auto) { t = a + b; a = b; return b = t; }).each(Log<BigInt>);

	// FizzBuzz (1, 2, Fizz, 4, Buzz, .., Buzz)
	Range(1, 100).map([](auto n){ return n % 15 == 0 ? L"FizzBuzz"
									   : n %  3 == 0 ? L"Fizz"
									   : n %  5 == 0 ? L"Buzz"
									   : Format(n); }).each(Log<String>);
}


/*
reduce

DIGITS
Number
String & &&

Pad
*/