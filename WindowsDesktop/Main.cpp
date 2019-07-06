
# include <Siv3D.hpp>

void Main()
{
	// Pecita.otf をロードして使う
	const Font font1(50, U"example/font/Pecita/Pecita.otf");

	// AnnyantRoman.ttf をロードして使う
	const Font font2(50, U"example/font/AnnyantRoman/AnnyantRoman.ttf");

	// NotoSansCJKjp-Regular.otf をロードして使う
	const Font font3(50, U"example/font/NotoSansCJKjp/NotoSansCJKjp-Regular.otf");

	while (System::Update())
	{
		font1(U"Hello").draw(20, 20);

		font2(U"Hello, こんにちは").draw(20, 70);

		font3(U"你好、こんにちは、안녕하세요").draw(20, 120);
	}
}
