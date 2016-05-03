
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;
using namespace s3d::literals;

void Main()
{
	Grid<int32> g(4, 4, 1);

	g.at(0, 1) = 10;

	Log(g);

	RunTest();
}
