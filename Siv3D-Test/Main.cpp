
# include <Siv3D.hpp>

void Main()
{
	RenderStateBlock2D rsb(BlendState::Additive);

	while (System::Update())
	{
		for (auto i : step(4))
		{
			ViewportBlock2D vb(i % 2 * 320, i / 2 * 240, 320, 240);

			for (int32 n = 0; n < 20; ++n)
			{
				Circle(RandomVec2(320, 240), 40).draw(HSV(i * 90 + 45, 0.5));
			}
		}
	}
}


