# include <Siv3D.hpp> // OpenSiv3D v0.1.7
# include <HamFramework.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	Print << Square(1.5);

	Print << Square(20);

	Print << Square("1.00001"_bigF);

	Range(0, 10).map([](int n) {return Vec2(std::sin(n), std::cos(n)); }).each(Output);

	Print << L"--";

	Range(0, 10).map([](int n) {return Vec2(std::sin(n), std::cos(n)); }).map(Abs).each(Output);

	Print << Abs(Point(-2, 3));

	Print << Id("-1.00001"_bigF);
	
	while (System::Update())
	{

	}
}
