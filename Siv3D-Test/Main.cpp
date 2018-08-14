
# include <Siv3D.hpp>

void Main()
{
	const String s = U"Siv3D";
	
	Print << U"{}"_fmt(Array<int32>{1,2,3,4,5});

	Print << U"{:.1f}"_fmt(Circular(0.5, 0.123));

	Print << U"{:.1f}"_fmt(RectF(100).shearedX(2.25));

	Print << U"{2:.1f} {1} {0} {3} {4:*>8} {5:*>8}"_fmt(Palette::Red, Window::ClientRect(), Vec3(1.11,2.22,3.33), s, StringView(U"Siv"), U"Enrect");

	const Font font(30);

	const RectF rect(0.5, 0.5, 2.5);

	while (System::Update())
	{
		font(Cursor::Pos()).draw(20, 170);
		font(rect).draw(20, 230);

		font(U"{}"_fmt(Cursor::Pos())).draw(20, 330);
		font(U"{}"_fmt(rect)).draw(20, 390);
	}
}
