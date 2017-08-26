# include <Siv3D.hpp> // OpenSiv3D v0.1.7
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();

	auto [val, exp] = Math::Frexp(L"3.0"_bigF);

	Print << val;

	Print << exp;

	while (System::Update())
	{

	}
}