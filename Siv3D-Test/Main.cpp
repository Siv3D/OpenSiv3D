
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;

void Main()
{
	const Vec2 a = Circular(4, 0);

	const Vec2 b = Circular(Arg::r = 4, Arg::theta = 0);

	const Vec2 c = Circular(Arg::theta = 0, Arg::r = 4);

	Log(a == b && b == c);


	const Rect d(-64, -64, 128);

	const Rect e(Arg::center = Point(0, 0), 128);
	
	Log(d == e);
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