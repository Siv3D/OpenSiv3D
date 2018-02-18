
# include <Siv3D.hpp>

void Main()
{
	Image image(480, 480, Palette::White);

	DynamicTexture texture(image);

	while (System::Update())
	{
		if (MouseL.down())
		{
			Circle(Cursor::Pos(), 80).paintFrame(image, 2, 2, Color(255, 127, 0, 127));

			texture.fill(image);
		}

		if (MouseR.down())
		{
			Circle(Cursor::Pos(), 80).overwriteFrame(image, 2, 2, Color(255, 127, 0, 127));

			texture.fill(image);
		}

		texture.draw();
	}
}