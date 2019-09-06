# include <Siv3D.hpp> // OpenSiv3D v0.4.1

struct GameOfLife
{
	Float2 pixelSize;
	Float2 _unused;
};

void Main()
{
	Window::Resize(1280, 720);
	constexpr Size FieldSize(1280, 720);
	const PixelShader ps(U"example/shader/game_of_life.hlsl");
	const ConstantBuffer<GameOfLife> cb({ Float2(1.0f, 1.0f) / FieldSize });
	RenderTexture rt0(Image(FieldSize, Arg::generator = [](){ return Color(RandomBool() * 255); }));
	RenderTexture rt1(FieldSize, ColorF(0.0));

	while (System::Update())
	{
		{
			ScopedRenderStates2D sampler(SamplerState::ClampNearest);
			rt0.draw(ColorF(0.0, 1.0, 0.0));

			{
				Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);
				ScopedCustomShader2D shader(ps);
				ScopedRenderTarget2D target(rt1);
				rt0.draw();
			}
		}

		std::swap(rt0, rt1);
	}
}
