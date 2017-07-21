# include <Siv3D.hpp> // OpenSiv3D v0.1.6

void Main()
{
	Script script(L"example/script.txt");
	
	auto GetNumber = script.getFunction<int32(void)>(L"GetNumber");
	
	auto DrawCircle = script.getFunction<void(const Circle&, const ColorF&)>(L"DrawCircle");
	
	Print << GetNumber();
	
	while (System::Update())
	{	
		DrawCircle(Circle(Cursor::Pos(), 50), ColorF(1.0, 0.0, 0.0, 0.5));
	}
}
