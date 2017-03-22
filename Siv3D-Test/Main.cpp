
# include <Siv3D.hpp>

void Main()
{
	//Log << Window::GetState().windowSize;

	//for (const auto& monitor : System::EnumActiveMonitors())
	//{
	//	Log << monitor.workArea;
	//}

	while (System::Update())
	{
		const auto state = Window::GetState();

		Log << state.pos;

		if (KeyC.down())
		{
			Window::Centering();
		}

		//Log << state.focused;

		//for (const auto& monitor : System::EnumActiveMonitors())
		//{
		//	Log << monitor.workArea;
		//}

		//Graphics::SetBackground(HSV(Cursor::Pos().x * 0.5, 0.5, 1.0));
	}
}

