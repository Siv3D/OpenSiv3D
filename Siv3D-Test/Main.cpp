
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.5, 0.8, 0.6));

	double s0 = 20.0, s1 = 20, s2 = 20, s3 = 20;
	bool c0 = false, c1 = true, c2 = true, c3 = false;

	while (System::Update())
	{
		SimpleGUI::CheckBox(c0, U"Windows", Vec2(40, 40), 200);
		SimpleGUI::CheckBox(c1, U"macOS", Vec2(40, 80), 200);
		SimpleGUI::CheckBox(c2, U"Linux", Vec2(40, 120), 200, false);
		SimpleGUI::CheckBox(c3, U"iOS", Vec2(40, 160), 200, false);

		SimpleGUI::Button(U"OK", Vec2(40, 240), 150);
		SimpleGUI::Button(U"キャンセル", Vec2(200, 240), 150);

		SimpleGUI::Button(U"Yes", Vec2(40, 280), 150, false);
		SimpleGUI::Button(U"No", Vec2(200, 280), 150, false);

		SimpleGUI::Slider(s0, 0.0, 100.0, Vec2(40, 344), 340);
		SimpleGUI::Slider(s1, 0.0, 100.0, Vec2(40, 384), 340, false);

		SimpleGUI::VerticalSlider(s2, 100.0, 0.0, Vec2(400, 40), 380);
		SimpleGUI::VerticalSlider(s3, 100.0, 0.0, Vec2(440, 40), 380, false);
	}
}
