# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.9, 0.8, 0.7));
	const Texture tweet(Icon(0xf099, 40));
	const Font font(32, Typeface::Bold);

	while (System::Update())
	{
		RoundRect rr(20, 20, 370, 50, 8);

		rr.drawShadow(Vec2(2,2), 8, 1)
			.draw(ColorF(0.3, 0.7, 0.8))
			.drawFrame(1.5, 0, AlphaF(0.4));

		tweet.drawAt(50, 45);

		font(L"結果をツイートする").draw(80, 25);

		Cursor::SetStyle(rr.mouseOver() ? CursorStyle::Hand : CursorStyle::Default);	
	}
}