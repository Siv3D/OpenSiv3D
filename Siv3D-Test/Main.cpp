# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Graphics::SetBackground(Palette::Seagreen);

	const Font font(30, Typeface::Medium);
	const double keySize = font.fontSize() * 1.5;

	while (System::Update())
	{
		Vec2 penPos(40, 40);

		for (const auto& glyph : font(U"$ OK  % Cancel  @ Menu"))
		{
			if (glyph.codePoint == U'$')
			{
				penPos.x += InputDeviceSymbol::DrawAsGlyph(KeyZ, penPos, font, keySize);
				continue;
			}
			else if (glyph.codePoint == U'%')
			{
				penPos.x += InputDeviceSymbol::DrawAsGlyph(KeyX, penPos, font, keySize);
				continue;
			}
			else if (glyph.codePoint == U'@')
			{
				penPos.x += InputDeviceSymbol::DrawAsGlyph(KeyC, penPos, font, keySize);
				continue;
			}

			glyph.texture.draw(penPos + glyph.offset);
			penPos.x += glyph.xAdvance;
		}

		InputDeviceSymbol::DrawInteractive(KeyF1, Vec2(100, 200), font, keySize);
		InputDeviceSymbol::DrawInteractive(KeyUp, Vec2(100, 250), font, keySize);
		InputDeviceSymbol::DrawInteractive(KeyEnter, Vec2(100, 300), font, keySize);
		InputDeviceSymbol::DrawInteractive(KeyBackspace, Vec2(100, 350), font, keySize);
	}
}