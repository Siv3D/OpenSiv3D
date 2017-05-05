
# include <Siv3D.hpp>

void Main()
{
	const Array<Circle> circles(20, Arg::generator = []()
	{
		return Circle(RandomVec2(320, 240), 40);
	});

	RenderStateBlock2D blend(BlendState::Additive);

	while (System::Update())
	{
		if (KeyR.down())
		{
			Window::Resize(1280, 720);
		}

		for (auto i : step(4))
		{
			ViewportBlock2D viewport(i % 2 * 320, i / 2 * 240, 320, 240);

			for (const auto& circle : circles)
			{
				circle.draw(HSV(i * 90 + 45, 0.5));
			}
		}

		Ellipse(Cursor::Pos(), 80, 40).draw().drawFrame(0, 4, Palette::Red);
	}
}
