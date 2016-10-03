
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;
using namespace s3d::literals;

void Main()
{
	const Vec2 a = Circular(4, 0);

	const Vec2 b = Circular(Arg::r = 4, Arg::theta = 0);

	const Vec2 c = Circular(Arg::theta = 0, Arg::r = 4);

	Log(a == b && b == c);


	Rect rect;
	rect.x = 20;
	rect.y = 30;
	rect.w = 40;
	rect.h = 50;

	Log(rect.pos);
	Log(rect.size);
}




/*


void F1(Arg::theta_<double> t)
{
Log(t.value);
}

void F2(Arg::theta_<Vec2> t)
{
Log(t.value.x);
}
//F1(Arg::theta = 0.5);

//F2(Arg::theta = Vec2(2,2));

//const Point pos(0, 0);

//F2(Arg::theta = pos);

////F2(Arg::theta = 4.5);
*/