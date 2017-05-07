
# include <Siv3D.hpp>

void Main()
{
	const Array<Vec2> pts(400, Arg::generator = [](){
		return RandomVec2(Window::ClientRect());
	});

	RenderStateBlock2D blend(BlendState::Additive);
	
	while (System::Update())
	{
		for(auto i : Range(0, 99))
			Shape2D::Cross(16, 6, pts[i], i * 1_deg).draw(HSV(i));

		for (auto i : Range(100, 199))
			Shape2D::Star(20, pts[i], i * 1_deg).draw(HSV(i));

		for (auto i : Range(200, 299))
			Shape2D::Hexagon(20, pts[i], i * 1_deg).draw(HSV(i));

		for (auto i : Range(300, 399))
			Shape2D::NStar(8, 20, 4, pts[i], i * 1_deg).draw(HSV(i));
	}
}
