# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.3, 0.9, 0.4));

	const Font font1(40), font2(60), font3(120);
	
	while (System::Update())
	{
		font1(L"🌠あいうえおy^120-_123").draw(50, 100).drawFrame();
		font1(L"🌠あいうえおy^120-_123").boundingRect(50, 100).drawFrame(1, 0, Palette::Orange);

		font1(L"🌠あいうえお\ny^120-_123").draw(50, 300).drawFrame();
		font1(L"🌠あいうえお\ny^120-_123").boundingRect(50, 300).drawFrame(1, 0, Palette::Orange);

		//font1(L"Sivy3D").draw(50, 100 - font1.ascent());

		//font2(L"Sivy3D").draw(170, 100 - font2.ascent());

		//font3(L"Sivy3D").draw(340, 100 - font3.ascent());

		//font1(L"Xyz🌠").drawBase(50, 100);

		//font2(L"Xyz🌠").drawBase(170, 100);

		//font3(L"Xyz🌠").drawBase(340, 100);

		Vec2 penPos(50, 250);

		Line(50, 0, 50, 480).draw();
		Line(0, 100, 640, 100).draw();
		Line(0, 250, 640, 250).draw();

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
