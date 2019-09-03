
# include <Siv3D.hpp> // OpenSiv3D v0.4.1

void Main()
{
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	const Font font(60);

	const Texture cat(Emoji(U"🐈"));

	Vec2 catPos(640, 450);

	const Texture windmill(U"example/windmill.png");

	const PixelShader ps(U"example/shader/rgb_shift.hlsl");

	while (System::Update())
	{
		{
			ScopedCustomShader2D shader(ps);
			windmill.draw(10, 10);
		}

		font(U"Hello, Siv3D!🐣").drawAt(400, 400, Palette::Black);

		cat.resized(100 + Periodic::Sine0_1(1s) * 20).drawAt(catPos);

		Circle(Cursor::Pos(), 40).draw(ColorF(1, 0, 0, 0.5));

		if (KeyA.down())
		{
			Print << U"Hello!";
		}

		if (SimpleGUI::Button(U"Move the cat", Vec2(600, 20)))
		{
			catPos = RandomVec2(Scene::Rect());
		}
	}
}