# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		for (auto i : step(12))
		{
			Shape2D::Rhombus(20, 40, Circular(100, i * 30_deg) + Window::Center(), i * 30_deg)
				.draw(HSV(i*30));
		}
	}
}
