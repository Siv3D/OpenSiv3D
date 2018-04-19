
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.8, 0.9, 1.0));

	Window::Resize(800, 600);

	const Font font(52);

	while (System::Update())
	{
		font(U"横書き、サンプル。\n「かぎ括弧」\nニューヨーク\n――…").draw(20, 180, ColorF(0.25));

		Vec2 penPos(700, 20);

		for (const auto& glyph : font.getVerticalGlyphs(U"縦書き、サンプル。\n「かぎ括弧」\nニューヨーク\n――…"))
		{
			if (glyph.codePoint == U'\n')
			{
				penPos.x -= font.height();
				penPos.y = 20;
				continue;
			}

			glyph.texture.draw(penPos + glyph.offset, ColorF(0.25));

			penPos.y += glyph.yAdvance;
		}
	}
}
