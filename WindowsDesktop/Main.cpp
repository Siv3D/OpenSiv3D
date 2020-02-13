
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	Scene::SetBackground(ColorF(0.6, 0.9, 0.8));

	size_t index0 = 0, index1 = 0;

	while (System::Update())
	{
		SimpleGUI::HorizontalRadioButtons(index0, { U"Windows", U"macOS", U"Linux" }, Vec2(30, 30), unspecified);
	
		SimpleGUI::RadioButtons(index1, { U"Windows", U"macOS", U"Linux" }, Vec2(30, 70), unspecified);
	}
}
