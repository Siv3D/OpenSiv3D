
# include <Siv3D.hpp>

void Main()
{
	Image image(U"example/windmill.png");

	Image result;

	ImageProcessing::Canny(image, result, 5, 200);

	const Texture texture(result);

	while (System::Update())
	{
		texture.draw();
	}
}
