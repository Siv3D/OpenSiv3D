
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetTargetFrameRateHz(300);

	Image image(Window::Size(), Palette::White);

	DynamicTexture texture(image);

	while (System::Update())
	{
		if (MouseL.pressed())
		{
			Line(Cursor::PreviousPos(), Cursor::Pos()).overwrite(image, 8, Palette::Orange);

			texture.fill(image);
		}

		texture.draw();
	}
}