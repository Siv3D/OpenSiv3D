# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Window::Resize(1280, 720);

	Graphics::SetBackground(Palette::Darkgreen);

	const PlayingCard::Pack cardsPack(70, Palette::Red);

	Array<PlayingCard::Card> cards = PlayingCard::CreateDeck(13);

	while (System::Update())
	{
		size_t index = 0;

		for (auto y : step(5))
		{
			for (auto x : step(13))
			{
				const Vec2 pos(50 + 85 * x, 25 + 125 * y);

				if (cardsPack.region(pos).leftClicked())
				{
					cards[index].flip();
				}

				cardsPack(cards[index]).draw(pos);

				++index;
			}
		}
	}
}
