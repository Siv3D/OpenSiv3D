
# include <Siv3D.hpp>
# include "Test/Test.hpp"

void Main()
{
	Siv3D_RunTest();

	Console << MD5::FromFile(U"example/windmill.png").asString();

	getchar();
}
