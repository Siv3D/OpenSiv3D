# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.0, 0.9, 0.0));

	while (System::Update())
	{
		RoundRect r(Cursor::Pos() + Point(80, 80), 400, 200, 50);

		r.draw();


		RoundRect(Cursor::Pos() + Point(40, 40), 400, 200, 20).drawFrame(10, Palette::Red);
	}
}
