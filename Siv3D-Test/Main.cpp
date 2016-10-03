
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;
using namespace s3d::literals;

void Main()
{
	Array<Circular> circulars(10000);

	TimeProfiler tp;

	for(auto i : step(100))
	{
		tp.begin(L"a");
		circulars.each_index([](size_t i, Circular& c) { c = Circular(i, i); });
		tp.end();
	}

	for (auto i : step(100))
	{
		tp.begin(L"na");
		circulars.each_index([](size_t i, Circular& c) { c = Circular(Arg::theta = i, Arg::r = i); });
		tp.end();
	}

	//RunTest();
}
