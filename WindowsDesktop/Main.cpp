# include <Siv3D.hpp> // OpenSiv3D v0.6.3

void Main()
{
	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	Rect rect{ 36, 42, 100, 100 };
	RectF rectF{ 236, 242, 100, 100 };

	while (System::Update())
	{
		ClearPrint();

		Print << U"-- Rect Test --";
		Print << U"topY(): " << rect.topY();        // 42
		Print << U"leftX(): " << rect.leftX();      // 36
		Print << U"bottomY(): " << rect.bottomY();  // 142
		Print << U"rightX(): " << rect.rightX();    // 136
		Print << U"";
		Print << U"-- RectF Test --";
		Print << U"topY(): " << rectF.topY();       // 242
		Print << U"leftX(): " << rectF.leftX();     // 236
		Print << U"bottomY(): " << rectF.bottomY(); // 342
		Print << U"rightX(): " << rectF.rightX();   // 336
	}
}

//
// = アドバイス =
// Debug ビルドではプログラムの最適化がオフになります。
// 実行速度が遅いと感じた場合は Release ビルドを試しましょう。
// アプリをリリースするときにも、Release ビルドにするのを忘れないように！
//
// 思ったように動作しない場合は「デバッグの開始」でプログラムを実行すると、
// 出力ウィンドウに詳細なログが表示されるので、エラーの原因を見つけやすくなります。
//
// = お役立ちリンク | Quick Links =
//
// Siv3D リファレンス
// https://zenn.dev/reputeless/books/siv3d-documentation
//
// Siv3D Reference
// https://zenn.dev/reputeless/books/siv3d-documentation-en
//
// Siv3D コミュニティへの参加
// Slack や Twitter, BBS で気軽に質問や情報交換ができます。
// https://zenn.dev/reputeless/books/siv3d-documentation/viewer/community
//
// Siv3D User Community
// https://zenn.dev/reputeless/books/siv3d-documentation-en/viewer/community
//
// 新機能の提案やバグの報告 | Feedback
// https://github.com/Siv3D/OpenSiv3D/issues
//
