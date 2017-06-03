# include <Siv3D.hpp>

void Main()
{
	const Texture texture(L"example/siv3d-kun.png");

	const RoundRect rect(30, 30, 140, 140, 40);

	while (System::Update())
	{
		rect.draw(Palette::Skyblue);

		rect(texture(90, 5, 110)).draw();
	}
}
