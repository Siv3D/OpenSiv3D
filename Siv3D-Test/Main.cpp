
# include <Siv3D.hpp>

void Main()
{
	for (const auto& output : Graphics::EnumOutputs())
	{
		Log << L"---" << output.name;
		Log << output.desktopRect;
		Log << output.displayModes.map([](const DisplayMode& mode)
		{
			return Format(mode.size, L"@", mode.refreshRateHz, L"Hz");
		});
	}
	
	while (System::Update())
	{
		Graphics::SetBackground(HSV(Cursor::Pos().x * 0.5, 0.5, 1.0));
		
		if (KeyL.down())
		{
			Graphics::SetFullScreen(true, Size(800, 600), 0);
		}
		
		if (KeyR.down())
		{
			Graphics::SetFullScreen(true, Size(2560, 1080), 1);
		}
		
		if (KeyW.down())
		{
			Graphics::SetFullScreen(false, Size(1280, 720));
		}
	}
}
