
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

Size Sum()
{
	Size s(0, 0);

	for (auto p : step({ 3, 5 }))
	{
		s += p;
	}

	return s;
}

void Main()
{
	Size s = Sum();

	Log << s;
	
	while (System::Update())
	{
		Window::SetTitle(Profiler::FPS());

		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.2));
	}
}
