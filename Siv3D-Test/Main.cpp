# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	ScalableWindow::SetBaseSize(640, 480);

	Window::Resize(1280, 640);

	const int32 dotSize = 40;

	Grid<int32> dots(Window::BaseSize() / dotSize);

	Graphics::SetBackground(Palette::White);

	Circle circle(320, 240, 80);

	while (System::Update())
	{

		const auto transformer = ScalableWindow::CreateTransformer();

		for (auto p : step(dots.size()))
		{
			const Rect rect(p * dotSize, dotSize);

			if (rect.leftClicked())
			{
				++dots[p] %= 4;
			}

			rect.stretched(-1).draw(ColorF(0.95 - dots[p] * 0.3));
		}



		circle.moveBy(Cursor::DeltaF());

		Print << L"----";
		Print << Cursor::PreviousPos() << Cursor::Pos() << Cursor::Delta();
		Print << Cursor::PreviousPosF() << Cursor::PosF() << Cursor::DeltaF();// circle;

		circle.draw();


		ScalableWindow::DrawBlackBars(HSV(40, 0.2, 0.9));
	}
}