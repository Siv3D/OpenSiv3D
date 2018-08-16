
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.4, 0.6, 0.5));

	const Array<Texture> textures =
	{
		Texture(Icon(0xf5bf, 80)),
		Texture(Icon(0xf5cb, 80)),
		Texture(Icon(0xf5bd, 80)),
		Texture(Icon(0xf576, 80)),
		Texture(Icon(0xf61f, 80)),
		Texture(Icon(0xf5ee, 80)),
	};

	while (System::Update())
	{
		for (auto[i, texture] : Indexed(textures))
		{
			texture.drawAt(80 + i % 3 * 120, 80 + i / 3 * 120);
		}
	}
}
