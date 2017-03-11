
# include <Siv3D.hpp>

void Main()
{
	for (const auto& displayOutput : Graphics::EnumOutputs())
	{
		Console << L"-----" << displayOutput.name;
		Console << displayOutput.displayModes.map([](const auto& displayMode){
			return Format(displayMode.size, L"@", displayMode.refreshRateHz, L"Hz");
		});
	}

	while (System::Update())
	{
		if (KeyL.down())
		{
			Graphics::SetFullScreen(true, Size(2560, 1080), 1);
		}

		if (KeyR.down())
		{
			Graphics::SetFullScreen(true, Size(3840, 2160), 0);
		}

		if (KeyW.down())
		{
			Graphics::SetFullScreen(false, Size(1280, 720));
		}
	}
}
