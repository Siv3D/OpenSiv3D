
# include <Siv3D.hpp>
# include "Test/Test.hpp"

void Main()
{
	Graphics::SetBackground(Palette::White);

	double t = 0.0;

	while (System::Update())
	{
		t += System::DeltaTime();

		for (int32 i = 0; i < 36; ++i)
		{
			const double angle = i * 10_deg + t * 30_deg;

			const Vec2 pos = OffsetCircular(Window::Center(), 200, angle);

			RectF(25).setCenter(pos).rotated(angle).draw(HSV(i * 10));
		}
	}
}
