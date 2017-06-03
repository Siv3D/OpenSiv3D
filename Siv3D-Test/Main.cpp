# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.4, 0.4, 0.7));
	const Font font(30, Typeface::Default);
	const Rect box(20, 40, 500, font.height());
	const String text = L"あいうえお。12345-Abcdefg.,!?";
	const Array<int32> xAdvances = font(text).getXAdvances();
	size_t index = xAdvances.size();

	while (System::Update())
	{
		if (0 < index && KeyLeft.down())
		{
			--index;
		}
		else if (index < xAdvances.size() && KeyRight.down())
		{
			++index;
		}

		int32 xOffset = 0;

		for (size_t i = 0; i < index; ++i)
		{
			xOffset += xAdvances[i];
		}

		box.stretched(2).draw();
		font(text).draw(box.pos, Palette::Black);
		Rect(box.pos.movedBy(xOffset - 1, 0), 2, box.h).draw(Palette::Red);
	}
}