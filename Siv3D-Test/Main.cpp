# include <Siv3D.hpp> // OpenSiv3D v0.1.7
# include <HamFramework.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	MT11213b mt;
	SFMT19937_64 sfmt;
	TimeProfiler tp;

	Print << sizeof(mt);
	Print << sizeof(sfmt);

	double s = 0.0;

	for (auto n : step(100))
	{
		tp.begin(L"mt");
		for (auto i : step(1000000))
		{
			//mt();
			//std::uniform_int<int32>(1, 6)(mt);
			s += mt.generateReal() < 0.5;
		}
		tp.end();

		tp.begin(L"rb");
		for (auto i : step(1000000))
		{
			//mt();
			//std::uniform_int<int32>(1, 6)(mt);
			s += RandomBool(0.5);
		}
		tp.end();

		tp.begin(L"sfmt");
		for (auto i : step(1000000))
		{
			//sfmt();
			//std::uniform_int<int32>(1, 6)(sfmt);
			s += sfmt.generateReal() < 0.5;
		}
		tp.end();
	}

	Print << s;

	while (System::Update())
	{

	}
}