# include <Siv3D.hpp>
# include <HamFramework.hpp>

namespace App
{
	// target resolution
	constexpr Size BaseSize(1920, 1080);

	void SetupFullScreen()
	{
		ScalableWindow::SetBaseSize(BaseSize);

		const auto[displayIndex, displayMode]
			= OptimalScreen::Get(OptimalScreen::Preference::AspectMin, BaseSize);

		Graphics::SetFullScreen(true, displayMode.size, displayIndex, displayMode.refreshRateHz);

		Print << displayIndex << L":" << displayMode.size << L"@" << displayMode.refreshRateHz;
	}
}

void Main()
{
	App::SetupFullScreen();

	Graphics::SetBackground(ColorF(0.7, 0.9, 0.8));

	Tobii tobii;
	Print << !!tobii;
	Print << tobii.isConnected();
	GazeInfo gazeInfo;

	while (System::Update())
	{
		const auto transformer = ScalableWindow::CreateTransformer();

		if (tobii.hasNewFrame())
		{
			tobii.getFrame(gazeInfo);
		}

		if (!tobii.isConnected() && KeyS.down())
		{
			Print << tobii.reconnect();
		}

		ClearPrint();
		Print << gazeInfo.screenPos;
		Print << gazeInfo.clientPos;
		Print << gazeInfo.leftEyePos;
		Print << gazeInfo.rightEyePos;
		Print << gazeInfo.userPresence;
		Circle(gazeInfo.clientPos, 40).drawFrame();

		ScalableWindow::DrawBlackBars();
	}
}