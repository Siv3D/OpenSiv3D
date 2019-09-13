# include <Siv3D.hpp> // OpenSiv3D v0.4.1

void Main()
{
	MSRenderTexture rt(100, 100, ColorF(0.0, 1.0));
	Image image;

	while (System::Update())
	{
		if (MouseL.down())
		{
			{
				ScopedRenderTarget2D target(rt);
				Circle(50, 50, 40).draw();
			}
			Graphics2D::Flush();
			rt.resolve();
			rt.readAsImage(image);
			image.save(U"s.png");
		}
	}
}
