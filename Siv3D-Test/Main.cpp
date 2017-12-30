# include <Siv3D.hpp>

void Main()
{
	//const Script script(U"example/script.txt");	
	const Script script(Arg::code = TextReader(U"example/script.txt").readAll());

	if (!script || !script.compiled())
	{
		return;
	}

	const auto GetNumber	= script.getFunction<int32(void)>(U"GetNumber");
	const auto GetMessage	= script.getFunction<String(void)>(U"GetMessage");
	const auto DrawCircle	= script.getFunction<void(const Circle&, const ColorF&)>(U"DrawCircle");

	Print << GetNumber();
	Print << GetMessage();

	while (System::Update())
	{
		DrawCircle(Circle(Cursor::Pos(), 100), HSV(System::FrameCount()));
	}
}
