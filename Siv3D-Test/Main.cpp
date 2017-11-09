
# include <Siv3D.hpp>
# include "Test/Test.hpp"

void Main()
{
	Siv3D_RunTest();

	Logger << Line(640, 200, 0, 480).boundingRect().x;
	Logger << Line(640, 200, 0, 480).boundingRect().y;
	Logger << Line(640, 200, 0, 480).boundingRect().w;
	Logger << Line(640, 200, 0, 480).boundingRect().h;
}
