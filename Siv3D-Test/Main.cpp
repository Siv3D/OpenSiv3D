# include <Siv3D.hpp> // OpenSiv3D v0.1.7
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();

	auto p0 = MakeShared<__m128>();
	auto p1 = MakeShared<__m128>();
	auto p2 = MakeShared<__m128>();

	Print << (size_t)p0.get() % 16;
	Print << (size_t)p1.get() % 16;
	Print << (size_t)p2.get() % 16;

	while (System::Update())
	{

	}
}
