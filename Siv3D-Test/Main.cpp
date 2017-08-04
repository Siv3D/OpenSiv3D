# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	const Texture texture(Emoji(L"😆"), TextureDesc::Mipped);

	while (System::Update())
	{
		const Vec2 c = Cursor::Pos();

		Shape2D::RectBalloon(Rect(Arg::center(Window::Center()), 240, 120), Window::Center().lerp(c, 0.7)).draw();

		texture.scale(0.7).drawAt(c);
	}
}
