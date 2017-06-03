# include <Siv3D.hpp>

void Main()
{
	//Graphics::SetBackground(ColorF(0.4, 0.8, 0.6));

	const Texture texture(Emoji(L"🇪🇪"));

	const Texture texture2(Emoji::Hamburger);

	const Font font(20);

	while (System::Update())
	{
		texture.draw();

		texture2.draw(200, 200);

		font(L"ABCDE🐈あいうえお🍔abcde🇪🇪12345").draw();

		//Circle(200, 200, 80).drawShadow(Vec2(2, 2), 12, 4).draw();
	}
}
