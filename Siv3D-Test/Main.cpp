
# include <Siv3D.hpp>

void Main()
{
	Image image(U"example/windmill.png");

	image.brighten(80);

	const Texture texture(image);

	while (System::Update())
	{
		texture.draw();
	}
}
