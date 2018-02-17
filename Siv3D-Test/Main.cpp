
# include <Siv3D.hpp>

void Main()
{
	Image image(U"example/windmill.png");

	image.gaussianBlur(10, 10);

	const Texture texture(image);

	while (System::Update())
	{
		texture.draw();
	}
}
