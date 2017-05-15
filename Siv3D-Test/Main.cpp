
# include <Siv3D.hpp>

void Main()
{
	DynamicTexture texture;

	Image image(200, 200, Palette::White);

	size_t n = 0;

	while (System::Update())
	{
		if (n < image.num_pixels())
		{
			image[n / 200][n % 200] = Palette::Orange;

			++n;

			texture.fill(image);
		}

		texture.draw();
	}
}
