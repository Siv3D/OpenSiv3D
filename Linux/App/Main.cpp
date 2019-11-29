
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

void Main()
{
	Window::SetTitle(U"これはアプリケーションのタイトル");

	bool b = false;
	while(System::Update())
	{
		if(!b)
		{
			ToastNotificationProperty prop;
			prop.title = U"タイトルtitle";
			prop.message = U"本文honbun";
			prop.imagePath = U"../../../../libnotify/hokusai.png";

			NotificationID id;
			id = Platform::Linux::ToastNotification::Show(prop);
			Print(id);

			b =true;
		}
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
// Siv3D Slack (ユーザコミュニティ) への参加
// https://siv3d.github.io/ja-jp/community/community/
//
// 新機能の提案やバグの報告
// https://github.com/Siv3D/OpenSiv3D/issues
//
