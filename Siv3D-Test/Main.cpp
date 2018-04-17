
# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);

	Image image(800, 600, Palette::White);

	Emoji::LoadImage(U"🐈").paint(image, 30, 30);

	Emoji::LoadImage(U"🐎").paint(image, 80, 80);

	const Texture texture(image);

	while (System::Update())
	{
		texture.draw();
	}
}
