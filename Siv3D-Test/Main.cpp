# include <Siv3D.hpp>

void Main()
{
	const Texture texture(L"example/siv3d-kun.png");

	while (System::Update())
	{
		texture.drawAt(Cursor::Pos());
	}
}
