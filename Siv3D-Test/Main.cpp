
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;
using namespace s3d::literals;
using namespace std::literals;

void Main()
{	

	Image image(400, 400, Palette::Orange);

	TimeProfiler tp;

	{
		tp.begin(L"F");

		{
			image.saveBMP(L"a0.bmp");
			image.saveBMP(L"a1.bmp");
			image.saveBMP(L"a2.bmp");
			image.saveBMP(L"a3.bmp");
			image.saveBMP(L"a4.bmp");
		}

		tp.end();
	}

	{
		tp.begin(L"M");

		{
			image.saveBMP2(L"b0.bmp");
			image.saveBMP2(L"b1.bmp");
			image.saveBMP2(L"b2.bmp");
			image.saveBMP2(L"b3.bmp");
			image.saveBMP2(L"b4.bmp");
		}

		tp.end();
	}


	//RunTest();
}
