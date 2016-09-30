
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
	const auto N = 2'000'000;
	const auto fn = [](int32& n) { n = static_cast<int32>(Math::Fraction(n * 0.12345) * 100); };

	Array<int32> m0, m1, m2;
	m0 = m1 = m2 = Range(0, N);

	TimeProfiler tp;

	for (int i = 0; i < 10; ++i)
	{
		tp.begin(L"each");
		m0.each(fn);
		tp.end();
	}

	for (int i = 0; i < 10; ++i)
	{
		tp.begin(L"parallel_each x2");
		m1.parallel_each(fn, 2);
		tp.end();
	}

	for (int i = 0; i < 10; ++i)
	{
		tp.begin(L"parallel_each x8");
		m2.parallel_each(fn);
		tp.end();
	}



	size_t k1 = 0, k2 = 0;

	for (int i = 0; i < 10; ++i)
	{
		tp.begin(L"count_if");
		k1 += m0.count_if(Odd());
		tp.end();
	}

	for (int i = 0; i < 10; ++i)
	{
		tp.begin(L"parallel_count_if");
		k2 += m0.parallel_count_if(Odd());
		tp.end();
	}

	Log(m0 == m1 && m1 == m2);
	Log(k1 == k2);


	const int N2 = 1'000'000;
	const Array<int32> r1 = Range(0, N2);
	Array<double> dd;
	dd.reserve((N2+1)*22);

	for (int i = 0; i < 10; ++i)
	{
		tp.begin(L"map");
		dd.append(r1.map([](int n) {return std::sqrt(n) + Math::Fraction(n*0.123) + 0.1; }));
		tp.end();
	}

	for (int i = 0; i < 10; ++i)
	{
		tp.begin(L"parallel_map");
		dd.append(r1.parallel_map([](int n) { return std::sqrt(n) + Math::Fraction(n*0.123) + 0.1; }));
		tp.end();
	}

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

