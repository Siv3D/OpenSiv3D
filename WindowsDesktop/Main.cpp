# include <Siv3D.hpp> // OpenSiv3D v0.4.1

struct GaussianBlur
{
	Float2 pixelSize;
	Float2 direction;
};

void GaussianBlurH(
	const PixelShader& ps,
	ConstantBuffer<GaussianBlur>& cb,
	const TextureRegion& textureRegion, RenderTexture& rt)
{
	cb->pixelSize = Float2(1.0f, 1.0f) / textureRegion.texture.size();
	cb->direction = Float2(1.0f, 0.0f);
	Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);
	{
		ScopedCustomShader2D shader(ps);
		ScopedRenderTarget2D target(rt);
		textureRegion.draw();
	}
}

void GaussianBlurV(
	const PixelShader& ps,
	ConstantBuffer<GaussianBlur>& cb,
	const TextureRegion& textureRegion, RenderTexture& rt)
{
	cb->pixelSize = Float2(1.0f, 1.0f) / textureRegion.texture.size();
	cb->direction = Float2(0.0f, 1.0f);
	Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);
	{
		ScopedCustomShader2D shader(ps);
		ScopedRenderTarget2D target(rt);
		textureRegion.draw();
	}
}

void GaussianBlurHV(const PixelShader& ps,
	ConstantBuffer<GaussianBlur>& cb,
	const TextureRegion& textureRegion,
	RenderTexture& rt0,
	RenderTexture& rt1)
{
	cb->pixelSize = Float2(1.0f, 1.0f) / textureRegion.texture.size();
	cb->direction = Float2(1.0f, 0.0f);
	Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);
	{
		ScopedCustomShader2D shader(ps);

		{
			ScopedRenderTarget2D target(rt0);
			textureRegion.draw();
		}

		cb->direction = Float2(0.0f, 1.0f);
		Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);

		{
			ScopedRenderTarget2D target(rt1);
			rt0.draw();
		}
	}
}

void GaussianBlurHV_Half(const PixelShader& ps,
	ConstantBuffer<GaussianBlur>& cb,
	const TextureRegion& textureRegion,
	RenderTexture& rt0,
	RenderTexture& rt1)
{
	cb->pixelSize = Float2(1.0f, 1.0f) / textureRegion.texture.size();
	cb->direction = Float2(1.0f, 0.0f);
	Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);
	{
		ScopedCustomShader2D shader(ps);

		{
			ScopedRenderTarget2D target(rt0);
			textureRegion.scaled(0.5).draw();
		}

		cb->direction = Float2(0.0f, 1.0f);
		Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);

		{
			ScopedRenderTarget2D target(rt1);
			rt0.draw();
		}
	}
}

void GaussianBlurHV_N(const PixelShader& ps,
	ConstantBuffer<GaussianBlur>& cb,
	const TextureRegion& textureRegion,
	RenderTexture& rt0,
	RenderTexture& rt1,
	size_t n)
{
	if (n)
	{
		GaussianBlurHV(ps, cb, textureRegion, rt0, rt1);
		--n;
	}

	while (n--)
	{
		GaussianBlurHV(ps, cb, rt1, rt0, rt1);
	}
}

void Main()
{
	const PixelShader ps(U"example/shader/gaussian_blur.hlsl");
	const Texture texture(U"example/windmill.png");
	const Size size = texture.size();
	ConstantBuffer<GaussianBlur> cb;

	const Size regionSize(400, 300);
	RenderTexture rtA(regionSize / 2, ColorF(1.0, 1.0)), rtB(regionSize / 2, ColorF(1.0, 1.0));
	RenderTexture scene(800, 600, ColorF(0.8, 0.9, 1.0));

	// Create a new font
	const Font font(60);

	// Create a new texture that contains a cat emoji
	//const Array<std::pair<Texture, Vec2>> emojis =
	//{
	//	{ Texture(Emoji(U"🐈")), RandomVec2(Scene::Rect()) },
	//	{ Texture(Emoji(U"🍔")), RandomVec2(Scene::Rect()) },
	//	{ Texture(Emoji(U"🌳")), RandomVec2(Scene::Rect()) },
	//	{ Texture(Emoji(U"🌎")), RandomVec2(Scene::Rect()) },
	//};

	const Array<String> emojics =
	{
		U"🐈",U"🍔",U"🌳",U"🌎",
		U"🍉",U"🚧",U"🔥",U"🔑",
		U"🤔",U"💦",U"🐤",U"🏯",
	};
	const Array<Texture> emojis = emojics.map([](const String& s) { return Texture(Emoji(s)); });

	Vec2 catPos(640, 450);

	while (System::Update())
	{
		scene.clear(ColorF(0.2, 0.3, 0.4));
		{
			ScopedRenderTarget2D target(scene);

			for (auto [i, emoji] : Indexed(emojis))
			{
				emoji.resized(100 + Periodic::Sine0_1(1s) * 20).drawAt(100 + i % 4 * 200, 100 + i / 4 * 200);
			}

			// When [Move the cat] button is pushed
			if (SimpleGUI::ButtonAt(U"Gaussian blur", Vec2(400, 400)))
			{
			}
		}

		const Rect window(Arg::center = Cursor::Pos(), Size(400, 300));
		GaussianBlurHV_Half(ps, cb, scene(window), rtA, rtB);
		GaussianBlurHV_N(ps, cb, rtB, rtA, rtB, 10);
		scene.draw();
		rtB.scaled(2).draw(window.pos).draw(ColorF(0.3, 0.6, 1.0, 0.4));
	}
}
