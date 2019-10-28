
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

void Main()
{
	Window::Resize(1280, 720);
	
	Scene::SetBackground(ColorF(0.2, 0.3, 0.4));

	const Size size(1280 - 80, 720 - 80);

	double r = 15.0;

	PoissonDisk2D pd(size, r);

	while (System::Update())
	{
		for (const auto& point : pd.getPoints())
		{
			Circle(point, r/4).movedBy(40, 40).draw();
		}

		if (SimpleGUI::Slider(r, 10.0, 100.0, Vec2(10, 10)))
		{
			pd = PoissonDisk2D(size, r);
		}
	}
}
