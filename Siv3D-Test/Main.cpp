# include <Siv3D.hpp> //OpenSiv3D v0.1.5

void Main()
{
	const Texture texture(Image(L"example/windmill.png").mirror());

	while (System::Update())
	{
		texture.draw();
	}
}
