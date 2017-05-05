# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	double t = 0.0;

	Graphics2D::SetBlendState(BlendState::Additive);

	while (System::Update())
	{
		for (auto p : step(Size(100, 50)))
		{
			Circle(p * 6, 3).draw(Palette::Gray);
		}

		t += System::DeltaTime();

		for (int32 i = 0; i < 36; ++i)
		{
			const double angle = i * 10_deg + t;

			const Vec2 pos = Circular(200, angle) + Window::Center();

			RectF(25).setCenter(pos).rotated(angle).draw(HSV(i * 10));
		}
		
		Circle(Cursor::Pos(), 40).draw(ColorF(1,0,0,0.5));
	}
}
