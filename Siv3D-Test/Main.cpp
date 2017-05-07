
# include <Siv3D.hpp>

void Main()
{
	const Array<Circle> circles(20, Arg::generator = [](){
		return Circle(RandomVec2(320, 240), 40);
	});
	
	double t = 0.0;
	
	Graphics2D::SetScissorRect(Rect(10, 20, 600, 400));

	RenderStateBlock2D blend(BlendState::Additive, RasterizerState::WireframeCullNone);
	
	while (System::Update())
	{
		Window::SetTitle(Profiler::FPS(), L"FPS");

		t += System::DeltaTime();
		
		for (auto i : step(4))
		{
			ViewportBlock2D viewport(i % 2 * 320, i / 2 * 240, 320, 240);
			
			for (const auto& circle : circles)
			{
				circle.draw(HSV(i * 90 + 45, 0.5));
			}
		}
		
		RenderStateBlock2D blend2(BlendState::Default, RasterizerState::SolidCullBackScissor);
		
		for (int32 i = 0; i < 36; ++i)
		{
			const double angle = i * 10_deg + t * 30_deg;
			
			const Vec2 pos = Circular(200, angle) + Window::Center();
			
			RectF(25).setCenter(pos).rotated(angle).draw(HSV(i * 10));
		}
		
		Circle(Cursor::Pos(), 80).draw(ColorF(1.0, 0.5))
			.drawPie(90_deg, 120_deg, Palette::Orange)
			.drawArc(90_deg, 100_deg, 6, 0, Palette::Red);

		Rect(40).draw();

		Line(Window::Center(), Cursor::Pos()).draw(4, { Palette::Yellow, Palette::Red });

		Circle(200).drawFrame(5);

		Rect(100, 100, 200).drawFrame(3);
	}
}
