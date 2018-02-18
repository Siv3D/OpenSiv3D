
# include <Siv3D.hpp>

void Main()
{
	Image image(480, 480, Palette::White);

	DynamicTexture texture(image);

	while (System::Update())
	{
		if (MouseL.down())
		{
			Rect(Cursor::Pos(), 80).shearedX(30).paint(image, Color(255, 127, 0, 127));

			texture.fill(image);
		}

		if (MouseR.down())
		{
			Rect(Cursor::Pos(), 80).shearedX(30).overwrite(image, Color(255, 127, 0, 127));

			texture.fill(image);
		}

		texture.draw();
	}
}