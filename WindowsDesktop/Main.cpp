# include <Siv3D.hpp> // OpenSiv3D v0.4.2

void Main()
{
	while (System::Update())
	{
		//Circle(Scene::Center(), 400).draw(Palette::Yellow, Palette::Black);

		Ellipse(Scene::Center(), 800, 600).draw(ColorF(1.0), ColorF(0.0));
	}
}
