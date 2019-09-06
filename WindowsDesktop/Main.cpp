# include <Siv3D.hpp> // OpenSiv3D v0.4.1

void Main()
{
	Window::Resize(1600, 800);
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	constexpr Size size(200, 400);
	constexpr ColorF clearColor(0.0, 1.0);
	const Font font(15);

	Array<RenderTexture> rts;
	rts << RenderTexture(size, clearColor, TextureFormat::R8G8B8A8_Unorm);
	rts << RenderTexture(size, clearColor, TextureFormat::R16G16_Float);
	rts << RenderTexture(size, clearColor, TextureFormat::R32_Float);
	rts << RenderTexture(size, clearColor, TextureFormat::R10G10B10A2_Unorm);
	rts << RenderTexture(size, clearColor, TextureFormat::R11G11B10_UFloat);
	rts << RenderTexture(size, clearColor, TextureFormat::R16G16B16A16_Float);
	rts << RenderTexture(size, clearColor, TextureFormat::R32G32_Float);
	rts << RenderTexture(size, clearColor, TextureFormat::R32G32B32A32_Float);

	const std::array<double, 9> values = { -4.0, -2.0, -1.0, -0.5, 0.0, 0.5, 1.0, 2.0, 4.0 };

	for (const auto& rt : rts)
	{
		ScopedRenderTarget2D target(rt);

		for (auto [i, x] : Indexed(values))
		{
			Circle(20, 40 + i * 40, 20).draw(ColorF(x));

			Circle(60, 40 + i * 40, 20).draw(ColorF(x, 0, 0, 1));

			Circle(100, 40 + i * 40, 20).draw(ColorF(0, x, 0, 1));

			Circle(140, 40 + i * 40, 20).draw(ColorF(0, 0, x, 1));

			Circle(180, 40 + i * 40, 20).draw(ColorF(1, x));
		}
	}

	double d = 1.0;

	while (System::Update())
	{
		for (auto [i, rt] : Indexed(rts))
		{
			rt.draw(i * 200, 0, ColorF(d)).drawFrame(1, 0, ColorF(0.5));

			font(ToString(rt.getFormat())).draw(20 + i * 200, 410, ColorF(0.0));
		}

		SimpleGUI::Slider(U"{:.2}"_fmt(d), d, -2.0, 2.0, Vec2(50, 500), 80, 200);
	}
}
