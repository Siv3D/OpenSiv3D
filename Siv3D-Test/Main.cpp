# include <Siv3D.hpp>

void Main()
{
	const Font font(60, Typeface::Heavy);
	const Texture texture(Emoji(U'🍣'));

	while (System::Update())
	{
		font(L"Siv3D 🐑").draw();
		
		texture.drawAt(Window::Center());
	}
}
