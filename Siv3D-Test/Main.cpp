# include <Siv3D.hpp>

void Main()
{
	Image image(256, 256, Color(11,22,33));

	DynamicTexture texture(image);

	while (System::Update())
	{
		if (MouseL.down())
		{
			Circle(Cursor::Pos(), 80).paint(image, ColorF(1, 0.6));

			texture.fill(image);
		}

		if (MouseR.pressed())
		{
			Circle(Cursor::Pos(), 80).draw(ColorF(1,0.6));
		}
		else
		{
			texture.draw();
		}		
	}
}