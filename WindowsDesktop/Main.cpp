# include <Siv3D.hpp> // OpenSiv3D v0.4.1

void Main()
{
	MSRenderTexture msRen(400, 300);

	while (System::Update())
	{
		msRen.resolve();
		msRen.draw();

		msRen.clear(ColorF(HSV(Scene::Time()*60)));
		{
			ScopedRenderTarget2D target(msRen);
			Rect(Cursor::Pos(), 100, 40).rotated(45_deg).draw(ColorF(0.0));
		}
	}
}
