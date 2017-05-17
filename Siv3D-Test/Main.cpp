# include <Siv3D.hpp>

void Main()
{
	const Font font(L"engine/font/mplus-1p-regular.ttf", 32);

	while (System::Update())
	{
		font(L"OpenSiv3D でテキスト描画\nこんにちは。\nThe quick brown fox\n花鳥風月")
			.draw(Vec2(30,40), Palette::Orange);
	}
}
