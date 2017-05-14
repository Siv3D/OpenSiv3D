
# include <Siv3D.hpp>

void Main()
{
	const Texture texture(L"example/windmill.png");

	while (System::Update())
	{
		texture.rotate(30_deg).drawAt(Cursor::Pos()).drawFrame(0, 2);
	}
}
