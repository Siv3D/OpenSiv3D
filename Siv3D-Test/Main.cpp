# include <Siv3D.hpp>

void Main()
{
	const Font font(Typeface::Heavy, 32);

	while (System::Update())
	{
		font(L"OpenSiv3D でテキスト描画\nこんにちは。\nThe quick brown fox jumps\n花鳥風月")
			.draw(Vec2(20,20), Palette::Skyblue);
	}
}
