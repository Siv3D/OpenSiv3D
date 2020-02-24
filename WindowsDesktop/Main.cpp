
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	Scene::SetBackground(ColorF(1.0));
	const Texture emoji(Emoji(U"🐈"));

	Camera2D camera(Vec2(0, 0), 2.0);

	MSRenderTexture rtexture(Size(400, 300));

	while (System::Update())
	{
		camera.update();

		{
			auto t = camera.createTransformer();

			emoji.drawAt(0, 0);
		}

		rtexture.clear(Palette::White);
		{
			ScopedRenderTarget2D rt(rtexture);

			auto t = camera.createTransformer();

			emoji.drawAt(0, 0);
		}
		Graphics2D::Flush();
		rtexture.resolve();

		rtexture.draw(400, 300);
	}
}
