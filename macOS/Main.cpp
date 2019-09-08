
# include <Siv3D.hpp> // OpenSiv3D v0.4.1

struct PoissonDisk
{
	Float2 pixelSize;
	float discRadius;
	float _unused;
	static constexpr uint32 BindingPoint() { return 2; }
};

void Main()
{
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
	
	const Texture texture(U"example/windmill.png");
	const PixelShader ps(U"example/shader/poisson_disc.frag",
									{ { U"PSConstants2D", 1 }, { U"PoissonDisc", 2 } });
	
	ConstantBuffer<PoissonDisk> cb;
	double discRadius = 0.0;

	while (System::Update())
	{
		SimpleGUI::Slider(U"discRadius", discRadius, 0.0, 8.0, Vec2(10, 340), 120, 200);
		cb->pixelSize = Float2(1.0, 1.0) / texture.size();
		cb->discRadius = static_cast<float>(discRadius);
		{
			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, cb);
			ScopedCustomShader2D shader(ps);
			texture.draw(10, 10);
		}
	}
}
