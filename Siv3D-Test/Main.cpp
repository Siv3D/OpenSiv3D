# include <Siv3D.hpp>

void Main()
{
	const Array<Circle> circles(20, Arg::generator = [](){
		return Circle(RandomVec2(320, 240), 40);
	});
	
	RenderStateBlock2D blend(BlendState::Additive);

	const LineString line
	{
		{ 50, 100 },{ 600, 100 },
		{ 50, 200 },{ 600, 200 },
		{ 50, 300 },{ 600, 300 },
		{ 50, 400 }
	};

	while (System::Update())
	{
		for (auto i : step(4))
		{
			ViewportBlock2D viewport(i % 2 * 320, i / 2 * 240, 320, 240);
			
			for (const auto& circle : circles)
			{
				circle.draw(HSV(i * 90 + 45, 0.5));
			}
		}

		line.draw(3, Palette::Yellow);
		
		Circle(Cursor::Pos(), 80).draw();
	}
}
