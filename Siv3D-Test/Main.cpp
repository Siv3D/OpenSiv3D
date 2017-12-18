# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);

	Graphics::SetBackground(Palette::White);

	for (auto i : step(36))
	{
		const String name = Format(i);

		TextureAsset::Register(name, U"test/image/p/" + name + U".png", TextureDesc::Mipped, AssetParameter::LoadAsync());
	}

	while (System::Update())
	{
		for (auto i : step(36))
		{
			const String name = Format(i);

			const Rect rect(6 + i % 6 * 206, 6 + i / 6 * 118, 200, 112);

			if (TextureAsset::IsReady(name))
			{
				rect(TextureAsset(name)).draw();
			}
			else
			{
				rect.draw(ColorF(0.7));
			}
		}
	}
}
