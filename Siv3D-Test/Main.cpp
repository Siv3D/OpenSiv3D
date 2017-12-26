# include <Siv3D.hpp>

void Main()
{
	Print << 90_deg;

	Print << Sin(30_deg);

	const Texture texture(Emoji(U"🐕"));

	while (System::Update())
	{
		Rect(Arg::center = Window::Center(), 100).rotated(45_deg).draw();

		texture.rotated(-0.1_deg * Time::GetMillisec()).drawAt(150, 350);
	}
}