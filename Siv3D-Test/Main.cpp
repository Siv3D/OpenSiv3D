# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.4, 0.8, 0.6));

	const Image boxShadowImage(Resource(L"engine/texture/box-shadow/256.png"));

	const Array<Image> boxShadowImageMips =
	{
		Image(Resource(L"engine/texture/box-shadow/128.png")),
		Image(Resource(L"engine/texture/box-shadow/64.png")),
		Image(Resource(L"engine/texture/box-shadow/32.png")),
		Image(Resource(L"engine/texture/box-shadow/16.png")),
		Image(Resource(L"engine/texture/box-shadow/8.png")),
	};

	const Texture boxShadowTexture(boxShadowImage, boxShadowImageMips);

	double scale = 1.0;

	while (System::Update())
	{
		scale *= (1.0 + Mouse::Wheel() * 0.01);

		boxShadowTexture.scale(scale).draw(200, 200, ColorF(0.0, 0.5));
	}
}
