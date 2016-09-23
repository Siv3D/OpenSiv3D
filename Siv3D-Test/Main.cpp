
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


struct alignas(16) Vector
{
	Vector() = default;

	Vector(float _x, float _y, float _z, float _w)
		: x(_x)
		, y(_y)
		, z(_z)
		, w(_w) {}

	~Vector()
	{
		Log(L"~Vector");
	}

	float x, y, z, w;
};

void Main()
{

	auto pv = MakeUnique<Vector>(0.1f, 0.2f, 0.3f, 0.4f);

	auto p = MakeShared<Vector>(0.1f, 0.2f, 0.3f, 0.4f);

	Log(p->x, L"\n", p->y, L"\n", p->z, L"\n", p->w);

	auto p2 = MakeShared<String>(20, L'a');

	Log(*p2);

	RunTest();

	//Image(Grid<int>(100, 100, Range(0, 9999)).map([](int n) { return Color(n % 256); }))._saveBMP(L"img.bmp");
}

