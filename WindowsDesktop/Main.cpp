
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

void Main()
{
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	double dummy = 0.4;
	bool enabled = true;
	HSV hsv = Palette::White;

	while (System::Update())
	{
		ClearPrint();
		SimpleGUI::ColorPicker(hsv, Vec2(130, 40), enabled);
		Circle(130 + 80, 240, 60).draw(hsv);
		Print << 2_dp << hsv;

		SimpleGUI::Button(U"A", Vec2(20, 40), 100);
		SimpleGUI::Button(U"B", Vec2(20, 80), 100);
		SimpleGUI::Button(U"C", Vec2(20, 120), 100);
		SimpleGUI::Slider(dummy, Vec2(320, 40));
		SimpleGUI::CheckBox(enabled, U"enabled", Vec2(320, 80));
	}
}
