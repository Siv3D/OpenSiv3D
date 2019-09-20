# include <Siv3D.hpp> // OpenSiv3D v0.4.1

void Main()
{
	Grid<float> grid(40, 40, 1.0f);

	RenderTexture rt(grid);

	while (System::Update())
	{
		if (MouseL.down())
		{
			ScopedRenderTarget2D target(rt);
			ScopedRenderStates2D blend(BlendState::Additive);

			Circle(Cursor::Pos(), 20).draw(ColorF(0.5));
		}

		if (MouseR.down())
		{
			rt.read(grid);
			Logger << grid;
		}
	}
}
