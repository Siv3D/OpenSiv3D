
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		const Circle circle(320, 240, 80);

		circle.draw();

		if (circle.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
	}
}
