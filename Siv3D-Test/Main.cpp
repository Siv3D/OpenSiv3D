
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;
using namespace s3d::literals;

Array<int> Gen()
{
	Array<int> v(10);

	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i] = i;
	}

	return v;
}

void Main()
{
	//RunTest();

	for (int i = 0; i < 10; ++i)
	{
		RDTSC r;

		Log(Gen().shuffled());
	}

	Log(L"Siv3D!");
}
