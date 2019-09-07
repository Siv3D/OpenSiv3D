# include <Siv3D.hpp> // OpenSiv3D v0.4.1

void Main()
{
	MSRenderTexture msRen(400, 300);
	
	while (System::Update())
	{
		msRen.clear(Palette::Seagreen);
		{
			ScopedRenderTarget2D target(msRen);
			Rect(Arg::center(200, 150), 100, 40).rotated(Scene::Time() * 20_deg).draw();
		}
		
		Graphics2D::Flush();
		msRen.resolve();
		msRen.draw();
	}
}
