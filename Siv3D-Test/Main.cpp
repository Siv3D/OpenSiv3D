# include <Siv3D.hpp>

void Main()
{
	Graphics::SetTargetFrameRateHz(120);

	Graphics::SetBackground(Palette::White);

	double t = 0.0;

	while (System::Update())
	{
		Window::SetTitle(Profiler::FPS(), L"FPS");

		t += System::DeltaTime();

		for (int32 i = 0; i < 36; ++i)
		{
			const double angle = i * 10_deg + t;

			const Vec2 pos = Circular(200, angle) + Window::Center();

			RectF(25).setCenter(pos).rotated(angle).draw(HSV(i * 10));
		}
	}
}
