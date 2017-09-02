# include <Siv3D.hpp> // OpenSiv3D v0.1.7
# include <HamFramework.hpp>

void Main()
{
	const auto[displayIndex, displayMode] = OptimalScreen::Get(OptimalScreen::Preference::Min, Size(1280, 720));

	Print << displayIndex << L":" << displayMode.size << L"@" << displayMode.refreshRateHz;

	Graphics::SetFullScreen(true, displayMode.size, displayIndex, displayMode.refreshRateHz);

	while (System::Update())
	{
		Circle(Cursor::Pos(), 100).draw(ColorF(1.0, 0.0, 0.0, 0.5));
	}
}
