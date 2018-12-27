
# include <Siv3D.hpp> // OpenSiv3D v0.3.1

void Main()
{
	Graphics::SetBackground(ColorF(0.8, 0.9, 1.0));

	const Font font(60);

	const Texture textureCat(Emoji(U"🐈"), TextureDesc::Mipped);

	while (System::Update())
	{
		font(U"Hello, Siv3D!🐣").drawAt(Window::Center(), Palette::Black);

		font(Cursor::Pos()).draw(20, 500, ColorF(0.6));

		textureCat.resized(80).draw(700, 500);

		Circle(Cursor::Pos(), 60).draw(ColorF(1, 0, 0, 0.5));
	}
}
