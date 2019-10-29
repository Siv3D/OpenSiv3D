
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

void Main()
{
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	const Array<Texture> textures =
	{
		Texture(Icon(0xf8cc, 50)),
		Texture(Icon(0xf11c, 60)),
		Texture(Icon(0xf11b, 60)),
	};

	while (System::Update())
	{
		int32 x = 60;

		for (auto i : step(3))
		{
			textures[i].drawAt(x, 60, ColorF(0.25));

			x += textures[i].width() / 2 + textures[(i+1) % 3].width() / 2 + 25;
		}
	}
}
