# include <Siv3D.hpp> // OpenSiv3D v0.4.2

void Main()
{
	while (System::Update())
	{
		Circle(Scene::Center(), 400).draw(Palette::Yellow, Palette::Black);
	}
}
