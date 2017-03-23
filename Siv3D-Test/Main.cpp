
# include <Siv3D.hpp>

void Main()
{
	for(const auto& monitor : System::EnumActiveMonitors())
	{
		Log << L"----";
		Log << monitor.name;
		Log << monitor.id;
		Log << monitor.displayDeviceName;
		Log << monitor.displayRect;
		Log << monitor.workArea;
		Log << monitor.isPrimary;
	}
	
	Window::SetPos(Point(0, 64));
	
	while (System::Update())
	{
		Window::SetTitle(Cursor::ScreenPos());
		
		if(KeyU.down())
		{
			Window::Centering();
		}
		
		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.5, 0.5, 1.0));
	}
}

