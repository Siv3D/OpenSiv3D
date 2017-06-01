# include <Siv3D.hpp>

void Main()
{
	const Texture texture(L"example/siv3d-kun.png");

	while (System::Update())
	{
		Circle(100, 100, 80).draw(Palette::Skyblue)(texture(85, 0, 120)).draw();
	}
}
