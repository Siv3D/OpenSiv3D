
# include <Siv3D.hpp>

void Main()
{
	Image image(U"example/windmill.png");

	const Texture texture(image.border(20, 30, 40, 50));

	while (System::Update())
	{
		texture.draw();
	}
}
