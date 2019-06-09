# define SIV3D_WINDOWS_HIGH_DPI // Windows で最大解像度のフルスクリーンを実現するのに必要
# include <Siv3D.hpp>

void Main()
{
	// 現在のモニタで使用可能なフルスクリーン解像度を取得
	const Array<Size> resolutions = Graphics::GetFullscreenResolutions();

	if (!resolutions)
	{
		throw Error(U"フルスクリーンモードを利用できません。");
	}

	// 選択肢を作成
	const Array<String> options = resolutions.map(Format);

	// 最大のフルスクリーン解像度にする
	size_t index = resolutions.size() - 1;
	if (!Window::SetFullscreen(true, resolutions[index]))
	{
		throw Error(U"フルスクリーンモードへの切り替えに失敗しました。");
	}

	while (System::Update())
	{
		// 100px 四方の正方形で画面を埋める
		for (auto p : step(Scene::Size() / 100 + Point(1, 1)))
		{
			if (IsOdd(p.x + p.y))
			{
				Rect(p * 100, 100).draw(Palette::Seagreen);
			}
		}

		Circle(Cursor::Pos(), 20).draw();

		// フルスクリーン解像度を変更する
		if (SimpleGUI::RadioButtons(index, options, Vec2(20, 20)))
		{
			if (!Window::SetFullscreen(true, resolutions[index]))
			{
				throw Error(U"フルスクリーン解像度の切り替えに失敗しました。");
			}
		}
	}
}