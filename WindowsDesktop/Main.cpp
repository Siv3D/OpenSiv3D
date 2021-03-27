
# include <Siv3D.hpp> // OpenSiv3D v0.6

void Main()
{
	// 背景を水色にする
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// 大きさ 60 のフォントを用意
	const Font font{ 60 };
	
	// カラー絵文字フォントを用意
	const Font emojiFont{ 60, Typeface::ColorEmoji };
	
	// カラー絵文字を font に追加
	font.addFallback(emojiFont);

	// 画像を読み込む
	const Texture texture{ U"example/windmill.png" };

	// 絵文字のテクスチャを用意
	const Texture emoji{ U"🐈"_emoji };

	// 絵文字の座標
	Vec2 emojiPos{ 300, 150 };

	// テキストをデバッグ表示
	Print << U"Push [A] key";

	while (System::Update())
	{
		// 画像を (200, 200) の位置に描く
		texture.draw(200, 200);

		// テキストを画面の中心に描く
		font(U"Hello, Siv3D!🚀").drawAt(Scene::Center(), Palette::Black);

		// 大きさをアニメーションさせて表示する
		emoji.resized(100 + Periodic::Sine0_1(1s) * 20).drawAt(emojiPos);

		// マウスカーソルに追従する半透明の赤い円を描く
		Circle{ Cursor::Pos(), 40 }.draw(ColorF{ 1, 0, 0, 0.5 });

		// [A] キーが押されたら
		if (KeyA.down())
		{
			// あいさつをランダムに選んでデバッグ表示する
			Print << Sample({ U"Hello!", U"こんにちは", U"你好", U"안녕하세요?" });
		}

		// ボタンが押されたら
		if (SimpleGUI::Button(U"Button", Vec2{ 640, 40 }))
		{
			// 絵文字の座標を画面内のランダムな位置に移動する
			emojiPos = RandomVec2(Scene::Rect());
		}
	}
}
