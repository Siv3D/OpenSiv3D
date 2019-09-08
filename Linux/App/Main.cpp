# include <Siv3D.hpp> // OpenSiv3D v0.4.1

void Main()
{
	Window::Resize(960, 600);
	
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
	const Texture emoji(Emoji::CreateSilhouetteImage(U"🍎"));
	const Texture windmill(U"example/windmill.png");
	const PixelShader ps(U"example/shader/multiple_texture.frag",
						 {{ U"PSConstants2D", 1 }});
	RenderTexture renderTexture(480, 320);

	while (System::Update())
	{
		renderTexture.clear(ColorF(1.0, 0.0));
		{
			BlendState blend;
			blend.srcAlpha = Blend::One;
			ScopedRenderStates2D states(blend);
			ScopedRenderTarget2D target(renderTexture);
			emoji.scaled(2).rotated(Scene::Time() * 60_deg).drawAt(renderTexture.size() / 2);
		}
		
		Rect(0, 140, 480, 320).draw(Palette::Black).movedBy(480, 0).draw(Palette::White);
		renderTexture.draw(0, 140);
		
		Graphics2D::SetTexture(1, renderTexture);
		{
			ScopedCustomShader2D shader(ps);
			windmill.draw(480, 140);
		}
	}
}
