
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;

void Main()
{
	//Log(IsEven(20));
	//Log(IsEven(none)(20));

	Range(0, 10).map(IsEven).each(Log);

	//const auto range = Range(1, 100'000'000);
	//TimeProfiler tp;
	//size_t n = 0;

	//{
	//	tp.begin(L"count_if");
	//	n = range.count_if(IsPrime);
	//	tp.end();
	//}
	//Log(n);

	//{
	//	tp.begin(L"parallel_count_if");
	//	n = range.parallel_count_if(IsPrime);
	//	tp.end();
	//}
	//Log(n);
}
