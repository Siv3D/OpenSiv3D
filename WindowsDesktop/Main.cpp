
# include <Siv3D.hpp> // OpenSiv3D v0.4.1

void Show(double d)
{
	uint64 u;
	std::memcpy(&u, &d, sizeof(double));
	Print << U"{}@{:x}"_fmt(d, u);
}

void Main()
{
	double foo = 0.0;

	try
	{
		foo = Parse<float>(U"_");
	}
	catch (const ParseError & e)
	{
		Print << e.what();
	}

	try
	{
		foo = Parse<double>(U"abcd");
	}
	catch (const ParseError & e)
	{
		Print << e.what();
	}

	Show(Parse<double>(U"0.5"));
	Show(Parse<double>(U"inf"));
	Show(Parse<double>(U"-inf"));
	Show(Parse<double>(U"nan"));

	while (System::Update())
	{

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
