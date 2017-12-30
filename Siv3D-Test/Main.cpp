# include <Siv3D.hpp>

void Main()
{
	Script script(U"example/script.txt");

	auto f = script.getFunction<int(void)>(U"GetNumber");

	auto DrawCircle = script.getFunction<void(const Circle&, const ColorF&)>(U"DrawCircle");

	Print << f();

	while (System::Update())
	{
		DrawCircle(Circle(Cursor::Pos(), 100), HSV(System::FrameCount()));
	}
}
