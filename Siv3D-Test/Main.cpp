# include <Siv3D.hpp>

void Main()
{
	const Array<Circle> circles(20, Arg::generator = [](){
		return Circle(RandomVec2(320, 240), 40);
	});
	
	RenderStateBlock2D blend(BlendState::Additive);
	
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
		
		Circle(Cursor::Pos(), 80).draw();
	}
}
