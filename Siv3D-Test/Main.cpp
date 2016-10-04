
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;
using namespace std::literals;

void Main()
{
	const Array<int32> v(10, Arg::generator = RNG(1, 6));
	
	Log << v;
	
	//RunTest();
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


	int i = 0;

	Range(0, 36).map([](int32 d)
	{
		return Vec2(-1, 0).rotate(d * 10 / 360.0 * 2_pi);
	})
	.map([](const Vec2& v)
	{
		return -Circular9(v);
	})
	.each([&](const auto& c)
	{
		Log(i++*10 ,L":\t", (c.theta /2_pi * 360));
	});
*/
