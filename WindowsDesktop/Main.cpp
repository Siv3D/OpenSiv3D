# include <Siv3D.hpp> // OpenSiv3D v0.4.1

struct GameOfLife
{
	Float2 pixelSize;
	Float2 _unused;
	static constexpr uint32 BindingPoint() { return 1; }
};

void Main()
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF(0.5));
	constexpr Size FieldSize(1280, 720);
	const PixelShader ps(U"example/shader/game_of_life.hlsl");
	ConstantBuffer<GameOfLife> cb;
	cb->pixelSize = Float2(1.0f, 1.0f) / FieldSize;

	const Texture init(Image(FieldSize, Arg::generator = []() { return Color(RandomBool() * 255); }));	
	RenderTexture rt0(FieldSize, ColorF(0.0)), rt1(FieldSize, ColorF(0.0));
	{
		ScopedRenderTarget2D target(rt0);
		init.draw();
	}

	while (System::Update())
	{
		ScopedRenderStates2D sampler(SamplerState::ClampNearest);
		rt0.draw(ColorF(0.0, 1.0, 0.0));

		{
			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, cb);
			ScopedRenderTarget2D target(rt1);
			ScopedCustomShader2D shader(ps);
			rt0.draw();
		}

		std::swap(rt0, rt1);
	}
}
