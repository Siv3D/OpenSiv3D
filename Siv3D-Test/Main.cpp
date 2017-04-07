
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	while (System::Update())
	{
		Window::SetTitle(Profiler::FPS(), L"fps");
		
		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.5));
		
		if (KeyD.down())
		{
			Graphics::SetVSyncEnabled(false);
		}
		else if (KeyE.down())
		{
			Graphics::SetVSyncEnabled(true);
		}
	}
}
