
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	while (System::Update())
	{
		Window::SetTitle(L"{}fps: {}"_fmt(Profiler::FPS(), System::FrameCount()));
	}
}
