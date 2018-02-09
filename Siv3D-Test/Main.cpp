# include <Siv3D.hpp>

void Main()
{
	Image image(256, 256, Palette::Black);

	DynamicTexture texture(image);

	while (System::Update())
	{
		if (MouseL.pressed())
		{
			Cursor::Pos().paint(image, ColorF(1.0, 0.5));

			texture.fill(image);
		}

		texture.draw();
	}
}