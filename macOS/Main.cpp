
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	// 背景を水色にする
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
	
	// 大きさ 60 のフォントを用意
	const Font font(60);
	
	// 猫のテクスチャを用意
	const Texture cat(Emoji(U"🐈"));
	
	// 猫の座標
	Vec2 catPos(640, 450);
	
	while (System::Update())
	{
		// テキストを画面の中心に描く
		font(U"Hello, Siv3D!🐣").drawAt(Scene::Center(), Palette::Black);
		
		// 大きさをアニメーションさせて猫を表示する
		cat.resized(100 + Periodic::Sine0_1(1s) * 20).drawAt(catPos);
		
		// マウスカーソルに追従する半透明の赤い円を描く
		Circle(Cursor::Pos(), 40).draw(ColorF(1, 0, 0, 0.5));
		
		// [A] キーが押されたら
		if (KeyA.down())
		{
			// Hello とデバッグ表示する
			Print << U"Hello!";
		}
		
		// ボタンが押されたら
		if (SimpleGUI::Button(U"Move the cat", Vec2(600, 20)))
		{
			// 猫の座標を画面内のランダムな位置に移動する
			catPos = RandomVec2(Scene::Rect());
		}
	}
}

//
// = アドバイス =
// macOS 10.15 Catalina で、アプリケーションを起動するたびに
// ファイルアクセス許可のダイアログが表示される場合、プロジェクトのフォルダを
// User/アプリケーション に移動させることで通常は表示されなくなります。
// 特別なファイルシステム関数の使用や、Web カメラ、マイク使用時のダイアログは消せません。
//
// = お役立ちリンク =
//
// OpenSiv3D リファレンス
// https://siv3d.github.io/ja-jp/
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/basic/
//
// よくある間違い
// https://siv3d.github.io/ja-jp/articles/mistakes/
//
// サポートについて
// https://siv3d.github.io/ja-jp/support/support/
//
// Siv3D ユーザコミュニティ Slack への参加
// https://siv3d.github.io/ja-jp/community/community/
//
// 新機能の提案やバグの報告
// https://github.com/Siv3D/OpenSiv3D/issues
//
