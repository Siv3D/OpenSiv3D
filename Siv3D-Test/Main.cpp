# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Palette::Seagreen);

	const Font font(60, Typeface::Bold);
	const Texture texture(U"example/windmill.png");

	const Rect rectFont(100, 30, 400, 80);
	const Rect rectTexture(100, 200, 300, 200);

	Stopwatch stopwatch(true);
	
	while (System::Update())
	{
		const double t = stopwatch.sF();
		const double a = 0;// (Math::Sin(t * 4.0) * 0.5 + 0.5) * 0.25;

		rectFont.draw(ColorF(0.2)).drawFrame(0, 2);
		rectTexture.draw(ColorF(0.2)).drawFrame(0, 2);

		Vec2 penPos(550 - t * 150, 27);
		for (const auto& glyph : font(U"2017 ”N 12 ŒŽ 30 “ú (“y)"))
		{
			glyph.texture.draw(penPos + glyph.offset, AlphaF(a));
			glyph.texture.drawClipped(penPos + glyph.offset, rectFont);
			penPos.x += glyph.xAdvance;
		}

		texture.draw(550 - t * 100, 150, AlphaF(a));
		texture.drawClipped(550 - t * 100, 150, rectTexture);
	}
}
