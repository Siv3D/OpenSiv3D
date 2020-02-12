
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	RenderTexture r1(200, 200);
	RenderTexture r2(Size(200, 200));
	RenderTexture r3(200, 200, Palette::Orange);
	RenderTexture r4(Size(200, 200), Palette::Orange);
	RenderTexture r5(200, 200, TextureFormat::R8G8B8A8_Unorm);
	RenderTexture r6(Size(200, 200), TextureFormat::R8G8B8A8_Unorm);

	while (System::Update())
	{
		r1.draw(0, 0);
		r2.draw(200, 0);
		r3.draw(400, 0);
		r4.draw(600, 0);
		r5.draw(0, 200);
		r6.draw(200, 200);
	}
}
