
# include <Siv3D.hpp>

void Main()
{
	Image image(U"example/windmill.png");

	const Texture texture(image.mirrored());

	while (System::Update())
	{
		texture.draw();
	}
}
