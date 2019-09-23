
# include <Siv3D.hpp> // OpenSiv3D v0.4.1

void Main()
{

	EmojiList emojis(Resource(U"engine/emoji/noto7_dictionary.dat"));
	
	Print << emojis.getList().size();
	
	while (System::Update())
	{

	}
}
