
# include <Siv3D.hpp>

void Main()
{
	const Script script(U"example/script/test.txt");
	const auto SayHello = script.getFunction<void(void)>(U"SayHello");
	const auto Add = script.getFunction<int32(int32, int32)>(U"Add");
	const auto Show = script.getFunction<void(const String&)>(U"Show");
	const auto Increment = script.getFunction<void(int32&)>(U"Increment");
	const auto Append = script.getFunction<void(String&, const String&)>(U"Append");
	const auto Move = script.getFunction<void(Vec2&)>(U"Move");
	const auto Fill = script.getFunction<void(Image&, const Color&)>(U"Fill");

	SayHello();
	Print << Add(20, 5);
	Show(U"Siv3D");

	int32 n = 0;
	Increment(n); Increment(n); Increment(n);
	Print << n;

	String s = U"Hello, ";
	Append(s, U"Siv3D!");
	Print << s;

	Vec2 pos(400, 300);

	Image image(300, 200);
	Fill(image, Palette::Skyblue);
	const Texture texture(image);

	while (System::Update())
	{
		Move(pos);
	
		texture.draw();
		
		Circle(pos, 40).draw();
	}
}
