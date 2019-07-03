#include <iostream>
#include <Siv3D.hpp>

void Main()
{
	auto ip = Network::GetPrivateIPv4();
	std::cout << ip.value().toStr() << std::endl;

	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	const Font font(60);

	const Texture emoji(Emoji(U"🐈"));

	Vec2 emojiPos(650, 450);

	while (System::Update())
	{   
		font(U"Hello, Siv3D!🐣").drawAt(Scene::Center(), Palette::Black);

		font(Cursor::Pos()).draw(20, 500, ColorF(0.6));

		emoji.resized(80).drawAt(emojiPos);

		Circle(Cursor::Pos(), 40).draw(ColorF(1, 0, 0, 0.5));

		if (KeyA.down())
		{
			Print << U"Hello!";
		}

		if (SimpleGUI::Button(U"Move the cat", Vec2(600, 20)))
		{
			emojiPos = RandomVec2(Scene::Rect());
		}
	}
}
