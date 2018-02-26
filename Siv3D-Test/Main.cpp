
# include <Siv3D.hpp>

void Main()
{
	Image image(U"example/windmill.png");

	const Texture texture(image.erode(4));

	while (System::Update())
	{
		texture.draw();
	}
}
