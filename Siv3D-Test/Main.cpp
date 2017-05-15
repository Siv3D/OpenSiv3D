# include <Siv3D.hpp>

void Main()
{
	Graphics::SetTargetFrameRateHz(10);
	RenderStateBlock2D rs(SamplerState::ClampNearest);
	Image img(128, 96, Arg::generator = []() { return Color(Random(1), 0, 0); });
	DynamicTexture tex;

	while (System::Update())
	{
		for (auto b : step(img.size()))
		{
			int32 s = 0;
			for (auto d : step({ -1, -1 }, { 3, 3 }))
				s += img.getPixel_Repeat(b + d).r;

			img[b].b = (s == 3) || (img[b].r && s == 4);
		}

		tex.fill(img.forEach([](Color& p) { p.g = (p.r = p.b) ? 255 : 0; }));
		tex.scale(5).draw();
	}
}
