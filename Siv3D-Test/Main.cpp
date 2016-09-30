
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;
using namespace s3d::literals;
using namespace std::chrono_literals;

static constexpr wchar hexTable[16] =
{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

void Dump(const void* data, size_t size)
{
	if (data == nullptr || size == 0)
	{
		return;
	}

	const uint8* ptr = static_cast<const uint8*>(data);

	String result(size * 3 - 1, L'0');

	wchar* dst = &result[0];

	bool isFirst = true;

	while (size--)
	{
		if (isFirst == true)
		{
			isFirst = false;
		}
		else
		{
			*dst++ = L' ';
		}

		*dst++ = hexTable[(*ptr) >> 4];
		*dst++ = hexTable[(*ptr) & 0x0F];
		++ptr;
	}

	Log(result);
}


template <class Fty>
void Do(int32* begin, int32*end, Fty f)
{
	while (begin != end)
	{
		f(*begin);

		++begin;
	}
}

# include <thread>

void Main()
{
	TimeProfiler tp;

	Range(0, 10).asArray().parallel_each([](int n){ n; });

	const auto N = 5000_big;

	Array<BigInt> m0 = Range(0_big, N);
	for (int i = 0; i<10; ++i)
	{
		tp.begin(L"each");

		m0.each([](BigInt& n) { n = LCM(n, 123); });

		tp.end();
	}

	Array<BigInt> m1 = Range(0_big, N);
	for (int i = 0; i<10; ++i)
	{
		tp.begin(L"parallel_each x2");

		m1.parallel_each([](BigInt& n) { n = LCM(n, 123); }, 2);

		tp.end();
	}

	Array<BigInt> m2 = Range(0_big, N);
	for (int i = 0; i<10; ++i)
	{
		tp.begin(L"parallel_each x8");

		m2.parallel_each([](BigInt& n) { n = LCM(n, 123); });

		tp.end();
	}


	Array<BigInt> t1 = Range(0_big, N);
	Array<BigInt> t2 = Range(0_big, N);
	t1.parallel_eachA([](BigInt& n) { n = LCM(n, 123); });
	t2.parallel_each2([](BigInt& n) { n = LCM(n, 123); });

	Array<BigInt> m5 = Range(0_big, N);
	for (int i = 0; i<10; ++i)
	{
		tp.begin(L"parallel_eachA x2");

		m5.parallel_eachA([](BigInt& n) { n = LCM(n, 123); }, 2);

		tp.end();
	}

	Array<BigInt> m6 = Range(0_big, N);
	for (int i = 0; i<10; ++i)
	{
		tp.begin(L"parallel_eachA x8");

		m6.parallel_eachA([](BigInt& n) { n = LCM(n, 123); });

		tp.end();
	}

	Log(m0 == m1 && m1 == m2 && m2 == m5 && m5 == m6);

	//Log(m);

	const auto a = Math::Fraction(10.3f);
	const auto b = Math::Fraction(10.3);
	const auto c = Math::Fraction(10);
	const auto d = Math::Fraction(Float2{ 10.3, 10.5 });
	constexpr auto e = Math::Fraction(Point{ 10, 10 });

	const auto d1 = Math::Fmod(2, 2);
	const auto d2 = Math::Fmod(2, 2.0f);
	const auto d3 = Math::Fmod(2, 2.0);

	const auto d4 = Math::Fmod(2.2f, 2);
	const auto d5 = Math::Fmod(2.2f, 2.0f);
	const auto d6 = Math::Fmod(2.2f, 2.0);

	const auto d7 = Math::Fmod(2.2, 2);
	const auto d8 = Math::Fmod(2.2, 2.0f);
	const auto d9 = Math::Fmod(2.2, 2.0);

	const auto d10 = Math::Fmod(Point(2, 3), Point(2, 3));
	const auto d11 = Math::Fmod(Point(2, 3), Float2(2.2f, 3.3f));
	const auto d12 = Math::Fmod(Point(2, 3), Vec2(2.2, 3.3));

	const auto d13 = Math::Fmod(Float2(2, 3), Point(2, 3));
	const auto d14 = Math::Fmod(Float2(2, 3), Float2(2.2f, 3.3f));
	const auto d15 = Math::Fmod(Float2(2, 3), Vec2(2.2, 3.3));

	const auto d16 = Math::Fmod(Vec2(2, 3), Point(2, 3));
	const auto d17 = Math::Fmod(Vec2(2, 3), Float2(2.2f, 3.3f));
	const auto d18 = Math::Fmod(Vec2(2, 3), Vec2(2.2, 3.3));

	const int k = sizeof(CommonVector_t<Vec2, Point>);

	//RunTest();

	//Image(Grid<int>(100, 100, Range(0, 9999)).map([](int n) { return Color(n % 256); }))._saveBMP(L"img.bmp");
}

