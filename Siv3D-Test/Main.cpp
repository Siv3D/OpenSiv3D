# include <Siv3D.hpp>

void Main()
{
	const Texture sheep(Emoji(U'🐏'), TextureDesc::Mipped);

	while (System::Update())
	{
		sheep.resize(60).drawAt(Cursor::Pos());
	}
}
