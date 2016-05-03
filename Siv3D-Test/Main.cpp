
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;
using namespace s3d::literals;

void Main()
{
	Stopwatch s(true);

	RunTest();

	Log(s);

	Log(s.format(L"hh 時間 mm 分 ss 秒 xx"));
}
