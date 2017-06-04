# include <Siv3D.hpp>

void Main()
{
	const Font font(32);
	const Point pos(10, 10);
	String text;
	size_t cursorPos = 0;

	while (System::Update())
	{
		cursorPos = TextInput::UpdateText(text, cursorPos);
	
		if (0 < cursorPos && KeyLeft.down())
			--cursorPos;

		if (cursorPos < text.num_codePoints() && KeyRight.down())
			++cursorPos;

		const Array<int32> xAdvances = font(text).getXAdvances();
		int32 xOffset = 0;
		for (size_t i = 0; i < cursorPos; ++i)
			xOffset += xAdvances[i];
	
		font(text).draw(pos);
		Rect(xOffset - 1, 0, 2, font.height()).movedBy(pos).draw(Palette::Orange);
	}
}