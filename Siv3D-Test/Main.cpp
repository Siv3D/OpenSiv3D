
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	HTMLWriter html(L"test.html", L"HTMLWriter test");

	html.writeHeader(L"HTMLWriter でできること");

	html.writeHeader(L"標準的なエレメントの出力", 2);

	html.writeHeader(L"パラグラフ", 3);

	html.writeParagraph(L"あいうえお。\nかきくけこさしすせそ。");

	html.writeHeader(L"リスト", 3);

	html.writeList({ L"あいうえお", L"かきくけこ", L"さしすせそ" });

	html.writeHeader(L"順序付きリスト", 3);

	html.writeOrderedList({ L"あいうえお", L"かきくけこ", L"さしすせそ" });

	html.writeHeader(L"テーブル", 3);

	const Grid<String> contents({ 10, 3 }, Range(1, 30).map(Format));

	html.writeTable(contents);

	html.writeHeader(L"水平線", 3);

	html.writeLine();

	html.writeHeader(L"画像", 3);

	html.writeImage(Image(L"example/windmill.png"));

	html.writeImage(L"https://lh3.googleusercontent.com/-9zGo6MSn_bA/VDK3E6Ml6SI/AAAAAAAADco/H_gP9aa_Dlc/s800/feature1.png");

	html.writeImage(L"https://lh3.googleusercontent.com/-9zGo6MSn_bA/VDK3E6Ml6SI/AAAAAAAADco/H_gP9aa_Dlc/s800/feature1.png", Size(80, 80));

	while (System::Update())
	{
		Window::SetTitle(Profiler::FPS());

		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.2));
	}
}
