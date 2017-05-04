# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	double t = 0.0;

	Graphics2D::SetBlendState(BlendState::Additive);

	while (System::Update())
	{
		for (auto p : step(Size(20, 20)))
		{
			Circle(p * 20, 8).draw(Palette::Gray);
		}

		t += System::DeltaTime();

		for (int32 i = 0; i < 36; ++i)
		{
			const double angle = i * 10_deg + t;

			const Vec2 pos = Circular(200, angle) + Window::Center();

			RectF(25).setCenter(pos).rotated(angle).draw(HSV(i * 10));
		}
	}
}
