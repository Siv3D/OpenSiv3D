# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	ScalableWindow::SetBaseSize(640, 480);
	Window::Resize(1280, 720);
	Graphics::SetBackground(ColorF(0.3, 0.5, 0.3));

	const Array<Texture> textures = {
		Texture(Emoji(L"🏡"), TextureDesc::Mipped), Texture(Emoji(L"🏠"), TextureDesc::Mipped),
		Texture(Emoji(L"🏥"), TextureDesc::Mipped), Texture(Emoji(L"🏛️"), TextureDesc::Mipped),
		Texture(Emoji(L"🏗️"), TextureDesc::Mipped), Texture(Emoji(L"🏘️"), TextureDesc::Mipped),
		Texture(Emoji(L"🏢"), TextureDesc::Mipped), Texture(Emoji(L"🏫"), TextureDesc::Mipped),
		Texture(Emoji(L"🏦"), TextureDesc::Mipped), Texture(Emoji(L"🏤"), TextureDesc::Mipped),
		Texture(Emoji(L"🗼"), TextureDesc::Mipped), Texture(Emoji(L"⛪"), TextureDesc::Mipped),
		Texture(Emoji(L"🏭"), TextureDesc::Mipped), Texture(Emoji(L"🏬"), TextureDesc::Mipped),
	};

	Array<std::pair<Vec2, int32>> emojis;
	Camera2D camera;

	while (System::Update())
	{
		camera.update();
		const auto transformer = camera.createTransformer();
		const auto transformer2 = ScalableWindow::CreateTransformer();
		const RenderStateBlock2D sampler(SamplerState::ClampLinear);

		if (MouseL.down())
		{
			emojis.emplace_back(Cursor::Pos(), Random(textures.size() - 1));
		}

		for (const auto& emoji : emojis)
		{
			Circle(emoji.first, 20).draw();
		}

		ScalableWindow::DrawBlackBars(ColorF(0.0, 0.8));
		camera.draw(Palette::Orange);
	}
}
