
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	RunTest();
	
	Log << Range(0, 100).sum();
	
	Log << Range(0_big, 100_big).sum();
	
	Log << step(Vec2(10,10), 5, Vec2(0.5,0.5));
	
	Log << step(Vec2(10,10), 5, Vec2(0.5,0.5)).sum();

	Log << step(String(L""), 5, L'.');

	Log << step(String(L""), 5, L'.').sum();
	
	while (System::Update())
	{
		if (KeyQ.down() && System::ShowMessageBox(L"アプリを終了します。", MessageBoxButtons::OKCancel)
			== MessageBoxSelection::OK)
		{
			break;
		}
	}
}
