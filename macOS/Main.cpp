
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
	const Font font(60);
	const Texture cat(Emoji(U"🐈"));
	const PixelShader rgbShiftPS(U"example/shader/rgb_shift.frag");
	Vec2 catPos(640, 450);
	
	const Texture windmill(U"example/windmill.png");
	const PixelShader poissonDiscPS(U"example/shader/poisson_disc.frag",
									{ { U"PSConstants2D", 1 }, { U"PoissonDisc", 2 } });
	ConstantBuffer<PoissonDisk> poissonDiscCB;
	double discRadius = 0.0;
	
	RenderTexture rt(400, 600, Palette::Seagreen);
	
	while (System::Update())
	{
		rt.clear(HSV(Scene::Time() * 60, 0.5, 1.0));
		
		SimpleGUI::Slider(U"discRadius", discRadius, 0.0, 8.0, Vec2(10, 340), 120, 200);
		poissonDiscCB->pixelSize = Float2(1.0, 1.0) / windmill.size();
		poissonDiscCB->discRadius = static_cast<float>(discRadius);
		{
			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, poissonDiscCB);
			ScopedRenderTarget2D target(rt);
			{
				ScopedCustomShader2D shader(poissonDiscPS);
				windmill.draw(10, 10);
			}
			Circle(0,0,50).draw(Palette::White);
		}
		
		rt.scaled(0.5).draw();
		
		//*
		font(U"Hello, Siv3D!🐣").drawAt(400, 400, Palette::Black);
		
		cat.resized(100 + Periodic::Sine0_1(1s) * 20).drawAt(catPos);
		
		Circle(Cursor::Pos(), 40).draw(ColorF(1, 0, 0, 0.5));
		
		if (KeyA.down())
		{
			Print << U"Hello!";
		}
		
		if (SimpleGUI::Button(U"Move the cat", Vec2(600, 20)))
		{
			catPos = RandomVec2(Scene::Rect());
		}
		
		//*/
	}
}
