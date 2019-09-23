
# include <Siv3D.hpp> // OpenSiv3D v0.4.1

void Main()
{
	EmojiList emojis(Resource(U"engine/emoji/noto7_dictionary.dat"));

	Print << emojis.size();

	for (const auto& emoji : emojis)
	{
		Logger << emoji;
	}

	const size_t emojiCount = emojis.size();

	size_t index = 0;

	DynamicTexture dtex(Emoji::CreateImage(emojis[index]));

	while (System::Update())
	{
		if (MouseL.down())
		{
			++index %= emojiCount;

			dtex.fill(Emoji::CreateImage(emojis[index]));
		}

		dtex.draw();
	}
}
