# include <Siv3D.hpp>

void Main()
{
	const Font font(40);

	while (System::Update())
	{
		const Rect rect(Cursor::Pos(), 200, 100);

		const Line line(rect.center() + Vec2(-100, 100), rect.center() + Vec2(420, 100));

		const ColorF color(0.2, 0.8, 0.4);

		rect.draw(color);

		line.draw(3, color);

		font(L"Xyz🌠").boundingRect(Arg::bottomRight = rect.br()).drawFrame(1,0, Palette::Orange);

		font(L"Xyz🌠").region(Arg::bottomRight = rect.br()).drawFrame();

		font(L"Xyz🌠").draw(Arg::bottomRight = rect.br());//.drawFrame();

		font(L"Xyz🌠").drawBase(line.begin);//.drawFrame();

		font(L"Xyz🌠").drawBase(Arg::center = line.center());// .drawFrame();

		font(L"Xyz🌠").drawBase(Arg::right = line.end);// .drawFrame();
	}
}

/*
Font::drawAt()
フォント埋め込み
Font::region()


*/
