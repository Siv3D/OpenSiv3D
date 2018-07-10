
# include <Siv3D.hpp>

void Main()
{
	Image image(256, Palette::White);

	Rect(Arg::center(128, 128), 80).overwriteFrame(image, 2, 0, Palette::Red);

	image.floodFilled(Point(2, 2), Color(0, 127, 255), FloodFillConnectivity::Value4, 4, 4);

	Texture texture(image, TextureDesc::Mipped);

	while (System::Update())
	{
		texture.draw();
	}
}
