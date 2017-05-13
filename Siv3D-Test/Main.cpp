
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Palette::White);

	double t = 0.0;

	//ImageProcessing::GenerateMips(Image(L"example/windmill.png")).each_index([](size_t index, const Image& image)
	//{
	//	image.save(L"{}.png"_fmt(index));
	//});

	//const Image image(L"example/windmill.png");
	//Array<Image> mipmaps = ImageProcessing::GenerateMips(image);
	//mipmaps[3].fill(Palette::Red);
	
	const Texture texture(L"example/windmill.png", TextureDesc::Mipped);
	//const Texture texture(image, mipmaps);

	RenderStateBlock2D sampler(SamplerState::RepeatNearest);
	
	while (System::Update())
	{
		Window::SetTitle(Profiler::FPS(), L"FPS");

		t += System::DeltaTime();

		for (auto i : step(36))
		{
			const double angle = i * 10_deg + t * 30_deg;

			const Vec2 pos = Circular(200, angle) + Window::Center();

			RectF(25).setCenter(pos).rotated(angle).draw(HSV(i * 10));
		}

		Circle(Cursor::Pos(), 40).draw(ColorF(1.0, 0.0, 0.0, 0.5));

		texture.scale(Cursor::Pos().x / 100.0).drawAt(Window::Center());
	}
}
