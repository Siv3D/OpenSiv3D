
# include <Siv3D.hpp>

void Main()
{
	//const ManagedScript script(U"example/script.txt");

	Graphics::SetBackground(Palette::White);
	const Texture texure(U"example/siv3d-kun.png");
	const Texture texure2(U"example/windmill.png");

	while (System::Update())
	{
		BlendState blend;

		blend.writeR = true;
		blend.writeG = blend.writeB = false;
		RenderStateBlock2D r(blend);

		texure.draw();

		blend.writeG = true;
		blend.writeR = blend.writeB = false;
		r = RenderStateBlock2D(blend);

		texure.draw(5, 0);

		blend.writeB = true;
		blend.writeR = blend.writeG = false;
		r = RenderStateBlock2D(blend);

		texure.draw(10, 0);

		blend.writeR = blend.writeG = blend.writeB = true;
		r = RenderStateBlock2D(blend);

		texure2.draw(400, 0);


		//script.run();

	}
}
