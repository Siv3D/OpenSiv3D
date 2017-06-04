# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.2, 0.5, 0.3));

	//const Font font(50, L"engine/font/fontawesome/FontAwesome.otf");

	const Font font2(50);


	while (System::Update())
	{
		//font(L"\uf099").draw(50, 50);

		//Log << font(L"\uf099").getXAdvances()[0];

		ClearPrint();
	//	Print << font(L"u\f099").getXAdvances()[0];
	//	Print << Cursor::Pos();
	//	font2(L"ツイートする").draw(50 + font(L"\uf099").getXAdvances()[0], 50);
	}
}