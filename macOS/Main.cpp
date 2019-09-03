
# include <Siv3D.hpp> // OpenSiv3D v0.4.1

struct PoissonDisk
{
	static constexpr std::string_view Name()
	{
		return "PoissonDisk";
	}
	
	static constexpr uint32 BindingPoint()
	{
		return 2;
	}
	
	Float2 pixelSize;
	float discRadius;
	float _unused;
};

void Main()
{
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
	const Font font(60);
	const Texture cat(Emoji(U"🐈"));
	const PixelShader ps(U"example/shader/rgb_shift.frag", { { U"pscbSprite", 1 } });
	Vec2 catPos(640, 450);
	
	const Texture windmill(U"example/windmill.png");
	const PixelShader poissonDiscPS(U"example/shader/poisson_disc.frag", { { U"pscbSprite", 1 }, { U"PoissonDisc", 2 } });
	ConstantBuffer<PoissonDisk> poissonDiscCB;
	double discRadius = 0.0;

	while (System::Update())
	{
		SimpleGUI::Slider(U"discRadius", discRadius, 0.0, 8.0, Vec2(10, 340), 120, 200);
		poissonDiscCB->pixelSize = Float2(1.0, 1.0) / windmill.size();
		poissonDiscCB->discRadius = static_cast<float>(discRadius);
		{
			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, poissonDiscCB);
			ScopedCustomShader2D shader(poissonDiscPS);
			windmill.draw(10, 10);
		}
		
		/*
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
