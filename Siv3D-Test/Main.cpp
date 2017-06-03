# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.7, 0.9, 0.9));

	const Texture e1(Emoji(L"👩🏿‍🌾"));
	const Texture e2(Emoji(L"🇳🇵"));
	const Texture e3(Emoji(L"🏳️‍🌈"));

	while (System::Update())
	{
		e1.draw(20, 40);
		e2.draw(180, 40);
		e3.draw(340, 40);
	}
}
