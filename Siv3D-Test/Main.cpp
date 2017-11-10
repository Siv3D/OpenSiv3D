
# include <Siv3D.hpp>
# include "Test/Test.hpp"

void Main()
{
	//Siv3D_RunTest();


	INIWriter ini(U"out.ini");
	ini[U"Month.January"] = 1;
	ini[U"Month.March"] = 3;
	ini[U"Month.May"] = 5;
	ini[U"Month.July"] = 7;

	ini[U"Monday"] = 11;

	ini[U"Tuesday"] = 12;

	ini[U"Wednesday"] = 13;

	ini[U"Thursdat"] = 14;

	ini[U"Friday"] = 15;

	ini[U"Saturday"] = 16;

	ini[U"Month.December"] = 12;
}
