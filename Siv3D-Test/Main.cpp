# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Palette::White);
	const Font font(40);

	while (System::Update())
	{
		Vec2 penPos(20, 20);
		bool onTag = false;
		String tag;

		for (const auto& glyph : font.getGlyphs(L"計算#123+234#してくれる"))
		{
			if (glyph.codePoint == U'#')
			{
				if (onTag)
				{
					penPos.x += font(Eval(tag)).draw(penPos, Palette::Brown).w;
					tag.clear();
				}
				
				onTag = !onTag;
			}
			else if (onTag)
			{
				tag.push_back(static_cast<wchar>(glyph.codePoint));
			}
			else
			{
				glyph.texture.draw(penPos + glyph.offset, Palette::Black);
				penPos.x += glyph.xAdvance;
			}
		}
	}
}
