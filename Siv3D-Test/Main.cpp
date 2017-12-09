
# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "Test/Test.hpp"

void Main()
{
	Graphics::SetBackground(ColorF(0.1, 0.4, 0.6));

	const Texture cookie(Emoji(U"🍪"), TextureDesc::Mipped);
	const Font font(40, Typeface::Heavy);

	Array<Vec2> cookies(300, Arg::generator = []() {
		return RandomVec2({ 0, 640 }, { -20, 500 }); });
	double t = 0, s = 0, v = 0;
	int32 count = 0;

	while (System::Update())
	{
		const double d = System::DeltaTime();
		t += d;

		for (auto& c : cookies)
		{
			cookie.resize(40).drawAt(c, ColorF(0.8));
			c.y += d * 30.0;

			if (c.y > 500)
			{
				c.y -= 520;
			}
		}

		Rect(0, 360, 640, 120).draw(Arg::top = ColorF(0.5, 0.25, 0.1, 0.8),
			Arg::bottom = ColorF(0.5, 0.25, 0.1, 1.0));

		Rect(0, 50, 640, 50).draw(ColorF(0.0, 0.4));
		font(U"{} cookies"_fmt(count)).drawAt(320, 77);

		const Circle circle(320, 240, 80 + s * 0.5);
		circle.drawShadow(Vec2(2, 2), 12);
		Shape2D::NStar(10, 160, 70, circle.center, t * 0.2).draw(AlphaF(0.2));
		Shape2D::NStar(9, 140, 70, circle.center, -t * 0.2).draw(AlphaF(0.2));
		cookie.resize(156 + s).drawAt(circle.center);

		Cursor::SetStyle(circle.mouseOver() ? CursorStyle::Hand : CursorStyle::Default);
		count += circle.leftClicked();

		v = (v - s) * 0.6;
		s = circle.leftPressed() ? -16.0 : (s + v);
	}
}
