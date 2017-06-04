# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.2, 0.5, 0.3));

	const Font font(50);

	const Texture cat(Emoji(L"🐈")), dog(Emoji(L"🐕"));

	while (System::Update())
	{
		font(L"Hello, Siv3D!🐣").draw(50, 50, Palette::Yellow);

		cat.drawAt(100, 200);

		dog.drawAt(300, 200);
	}
}