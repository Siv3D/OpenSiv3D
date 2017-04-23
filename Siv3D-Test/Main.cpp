# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Palette::White);

	Circle circle(200, 200, 50);

	bool grabbed = false;

	while (System::Update())
	{
		if (circle.leftClicked())
		{
			grabbed = true;
		}
		else if (MouseL.up())
		{
			grabbed = false;
		}
		else if (grabbed)
		{
			circle.moveBy(Cursor::Delta());
		}

		const bool handCursor = circle.mouseOver();

		if (grabbed)
		{
			// つかんでいる場合、円の影を描く
			circle.movedBy(2,2).draw(Palette::Gray);
		}

		circle.draw(Palette::Skyblue);
	}
}