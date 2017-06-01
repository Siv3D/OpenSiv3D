# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.4, 0.8, 0.6));

	const Font font(20);

	const String text = L" Siv3D（http://siv3d.jp) は，音や画像を使ったプログラムや，マイク，Web カメラ，Kinect など様々なデバイスを使ったアプリケーションを，シンプルな C++ コードで開発できるフレームワークである．最新の C++ 規格を活用する，豊富なアプリケーション・プログラミング・インタフェース (API) により，お絵かきアプリは 9 行，Kinect を用いた人の姿勢のキャプチャは 15 行，ブロックくずしゲームは 28 行といったように，複雑なインタラクションを短いコードで記述できるのが特徴である．";

	Rect rect(40, 40, 100, 100);

	while (System::Update())
	{
		const int32 w = Max(Cursor::Pos().x - 50, 80);
		const int32 h = Max(Cursor::Pos().y - 50, font.height() + 10);
		rect.setSize(w, h);

		rect.draw();

		if (!font(text).draw(rect.stretched(-5), Palette::Black))
		{
			rect.drawFrame(0, 6, Palette::Red);
		}
	}
}
