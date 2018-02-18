
# include <Siv3D.hpp>


void Main()
{
	Image image(U"example/windmill.png");

	Rect(0, 0, 400, 80).overwrite(image, Palette::Red);

	const Texture texture(image.spreaded(8, 8));

	while (System::Update())
	{
		texture.draw();
	}
}
