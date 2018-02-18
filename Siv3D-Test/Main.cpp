
# include <Siv3D.hpp>

void Main()
{
	Image image(480, 480, Palette::White);

	DynamicTexture texture(image);

	// ü‚ğì¬
	const LineString line
	{
		Vec2(50, 100), Vec2(600, 100),
		Vec2(50, 200), Vec2(600, 200),
		Vec2(50, 300), Vec2(600, 300),
		Vec2(50, 400)
	};

	while (System::Update())
	{
		if (MouseL.down())
		{
			line.paint(image, 10, Color(255, 127, 0, 127), true);

			texture.fill(image);
		}

		if (MouseR.down())
		{
			line.overwrite(image, 10, Color(255, 127, 0, 127), true);

			texture.fill(image);
		}

		texture.draw();
	}
}