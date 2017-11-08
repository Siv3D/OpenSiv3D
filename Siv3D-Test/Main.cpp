
# include <Siv3D.hpp>
# include "Test/Test.hpp"

void Main()
{
	Siv3D_RunTest();

	Logger << MD5::FromFile(U"example/windmill.png");
}
