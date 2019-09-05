# include <Siv3D.hpp> // OpenSiv3D v0.4.1

void Main()
{
	Window::Resize(1600, 600);
	
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
	const Texture emoji(Emoji(U"😇"));
	RenderTexture renderTexture(600, 600, Palette::White);
	
	Image image(renderTexture.size(), Palette::White);
	DynamicTexture dynamicTexture(image);
	
	while (System::Update())
	{
		if (MouseL.pressed())
		{
			{
				ScopedRenderTarget2D target(renderTexture);
				emoji.drawAt(Cursor::Pos());
			}
			renderTexture.readAsImage(image);
			image.dilate(3);
			dynamicTexture.fill(image);
		}
		
		renderTexture.draw();
		emoji.drawAt(Cursor::Pos());
		
		if (SimpleGUI::Button(U"Clear", Vec2(620, 20)))
		{
			renderTexture.clear(Palette::White);
		}
		
		dynamicTexture.draw(800, 0);
	}
}
