
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	Log << EnumResourceFiles();

	Window::Resize(1280, 720);

	while (System::Update())
	{
		if (KeyR.down())
		{
			Graphics::SetFullScreen(false, Size(800, 600));
		}

		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.2));
	}
}
