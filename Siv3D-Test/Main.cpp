# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	const Size baseSize(720, 720);

	ScalableWindow::SetBaseSize(baseSize);

	const auto[displayIndex, displayMode]
		= OptimalScreen::Get(OptimalScreen::Preference::AspectMin, baseSize);

	Print << displayIndex << L":" << displayMode.size << L"@" << displayMode.refreshRateHz;

	Graphics::SetFullScreen(true, displayMode.size, displayIndex, displayMode.refreshRateHz);

	Graphics::SetBackground(ColorF(0.7, 0.9, 0.8));

	while (System::Update())
	{
		const auto t = ScalableWindow::CreateTransformer();

		Circle(Cursor::Pos(), 100).draw();

		ScalableWindow::DrawBlackBars(ColorF(0.0));
	}
}