
# include <Siv3D.hpp> // OpenSiv3D v0.4.1 pre

void Main()
{
	Scene::Resize(256, 256);
	
	//Window::Resize(256, 256);
	Scene::SetTextureFilter(TextureFilter::Nearest);
	
	while (System::Update())
	{
		Circle(128, 128, 60).draw();
		
		if (KeyS.down())
		{
			ScreenCapture::SaveCurrentFrame();
		}
	}
}
