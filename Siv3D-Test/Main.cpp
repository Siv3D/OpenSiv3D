# include <Siv3D.hpp>

void Main()
{
	const Font font(32);
	const Point pos(10, 40);
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
	
		const int32 lines = (int32)text.count(L'\n');
		font(text).draw(pos);
		
		const String markedText = TextInput::GetMarkedText();
		font(markedText).draw(pos.movedBy(xOffset, 0), Palette::Gray);
		
		const Array<int32> xAdvances2 = font(markedText).getXAdvances();
		for (size_t i = 0; i < xAdvances2.size(); ++i)
			xOffset += xAdvances2[i];
		Rect(xOffset - 1, font.height() * lines, 2, font.height()).movedBy(pos).draw(Palette::Orange);
	}
}
