# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.3, 0.9, 0.4));

	const Font font1(40), font2(60), font3(120);

	Log << font1.familyName() << L"-" << font1.styleName();

	while (System::Update())
	{
		Line(50, 0, 50, 480).draw();
		Line(0, 250, 640, 250).draw();

		Vec2 penPos(50, 250);

		for (const auto& glyph : font1(L"Hello, Siv3D!Xyz🌠"))
		{
			if (glyph.codePoint == U'S')
			{
				const auto glyph2 = font3.getGlyph(U'S');
				glyph2.texture.draw(penPos + Vec2(glyph2.offset.x, -glyph2.bearingY));
				penPos.x += glyph2.xAdvance;
			}
			else
			{
				glyph.texture.draw(penPos + Vec2(glyph.offset.x, -glyph.bearingY));
				penPos.x += glyph.xAdvance;
			}
		}
	}
}
