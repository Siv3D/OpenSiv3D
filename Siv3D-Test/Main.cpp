
# include <Siv3D.hpp>

void Main()
{
	Image image(480, 480, Palette::White);

	DynamicTexture texture(image);

	while (System::Update())
	{
		if (MouseL.down())
		{
			Line(Cursor::Pos(), 80, 40).paintArrow(image, 10, Vec2(10, 10), Color(255, 127, 0, 127));

			texture.fill(image);
		}

		if (MouseR.down())
		{
			Line(Cursor::Pos(), 380, 40).overwriteArrow(image, 10, Vec2(10, 10), Color(255, 127, 0, 127));

			texture.fill(image);
		}

		texture.draw();
	}
}