
# include <Siv3D.hpp>

inline float Smoothstep(float min, float max, float x)
{
	if (x <= min)
	{
		return 0.0f;
	}
	else if (max <= x)
	{
		return 1.0f;
	}

	x = (x - min) / (max - min);

	return x*x*(3.0f - 2.0f*x);
}

const Image CreateGradation()
{
	Image image(1, 512);

	for (int32 y = 0; y <= 255; ++y)
	{
		image[y][0] = ColorF(Smoothstep(0, 1, y / 255.0));
	}

	for (int32 y = 256; y < 512; ++y)
	{
		image[y][0] = ColorF(Smoothstep(0, 1, (511 - y) / 255.0));
	}

	return image;
}

void Main()
{
	const Texture texture(CreateGradation(), TextureDesc::Mipped);

	const int size = 640;
	const int vSize = size * 2;
	const int iSize = (size - 1) * 6;

	Sprite sprite(vSize, iSize);

	for (auto i : step(size))
	{
		sprite.vertices[i * 2 + 0].pos = Float2(i, 10);
		sprite.vertices[i * 2 + 0].color.set(1.0, 0.5, 1.0, 1.0);
		sprite.vertices[i * 2 + 0].tex.set(0.0, 0.0);

		sprite.vertices[i * 2 + 1].pos = Float2(i, 50);
		sprite.vertices[i * 2 + 1].color.set(1.0, 0.35, 1.0, 1.0);
		sprite.vertices[i * 2 + 1].tex.set(0.0, 1.0);
	}

	for (uint16 i = 0; i < size - 1; ++i)
	{
		sprite.indices[i * 6 + 0] = i * 2 + 0;
		sprite.indices[i * 6 + 1] = i * 2 + 2;
		sprite.indices[i * 6 + 2] = i * 2 + 1;

		sprite.indices[i * 6 + 3] = i * 2 + 3;
		sprite.indices[i * 6 + 4] = i * 2 + 1;
		sprite.indices[i * 6 + 5] = i * 2 + 2;
	}

	//Graphics2D::SetBlendState(BlendState::Additive);

	RenderStateBlock2D blend(BlendState::Additive);

	PerlinNoise noise;

	while (System::Update())
	{
		const int32 count = System::FrameCount();

		for (auto n : step(6))
		{
			const ColorF color = HSV(n * 20 + count % 360).toColor(96);

			for (auto i : step(size))
			{
				const double t = count *0.4f + i *0.05f + n * 2.0f;
				const double a = 200 + noise.noise(t*0.015) * 300;
				const double b = a + 40 + noise.noise(t*0.05) * 40;

				sprite.vertices[i * 2 + 0].pos = Float2(i, a);
				sprite.vertices[i * 2 + 0].color = color.rgba();

				sprite.vertices[i * 2 + 1].pos = Float2(i, b);
				sprite.vertices[i * 2 + 1].color = color.rgba();
			}

			sprite.draw(texture);
		}
	}
}