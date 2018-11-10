
# include <Siv3D.hpp>

void Main()
{
	

	while (System::Update())
	{
		if (KeyA.down())
		{
			Clipboard::SetText(U"AAA");
		}

		if (KeyB.down())
		{
			Clipboard::SetText(U"BBB");
		}

		if (KeyC.down())
		{
			Clipboard::SetText(U"CCC");
		}

		if (KeyD.down())
		{
			String text;
			Clipboard::GetText(text);
			Print << text;
		}
	}
}
