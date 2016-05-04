
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;
using namespace s3d::literals;
using namespace std::chrono_literals;

void Main()
{
	MillisecClock m;

	RunTest();

	m.log();
}
