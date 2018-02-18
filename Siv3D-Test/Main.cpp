
# include <Siv3D.hpp>

void Main()
{
	Image image(480, 480, Palette::White);

	DynamicTexture texture(image);

	while (System::Update())
	{
		if (MouseL.down())
		{
			Triangle(Cursor::Pos(), 80).paint(image, Color(255, 127, 0, 127));

			texture.fill(image);
		}

		if (MouseR.down())
		{
			Triangle(Cursor::Pos(), 80).overwrite(image, Color(255, 127, 0, 127));

			texture.fill(image);
		}

		texture.draw();
	}
}