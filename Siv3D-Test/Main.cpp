
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.5, 0.8, 0.6));

	TextEditState text(U"テキスト入力"), text2, text3(U"あいうえお"), text4;
	
	double s0 = 20.0, s1 = 20, s2 = 20, s3 = 20;
	
	bool c0 = false, c1 = true, c2 = true, c3 = false;

	while (System::Update())
	{
		SimpleGUI::TextBox(text, Vec2(40, 40), 200, 8);
		SimpleGUI::TextBox(text2, Vec2(40, 80), 200, 8);
		SimpleGUI::TextBox(text3, Vec2(40, 120), 200, 16, false);
		SimpleGUI::TextBox(text4, Vec2(40, 160), 200, 16, false);

		SimpleGUI::CheckBox(c0, U"Windows", Vec2(260, 40), 160);
		SimpleGUI::CheckBox(c1, U"macOS", Vec2(260, 80), 160);
		SimpleGUI::CheckBox(c2, U"Linux", Vec2(260, 120), 160, false);
		SimpleGUI::CheckBox(c3, U"iOS", Vec2(260, 160), 160, false);

		SimpleGUI::Button(U"OK", Vec2(40, 210), 150);
		SimpleGUI::Button(U"キャンセル", Vec2(200, 210), 150);
		SimpleGUI::Button(U"Yes", Vec2(40, 250), 150, false);
		SimpleGUI::Button(U"No", Vec2(200, 250), 150, false);

		SimpleGUI::Slider(s0, 0.0, 100.0, Vec2(40, 304), 400);
		SimpleGUI::Slider(s1, 0.0, 100.0, Vec2(40, 344), 400, false);
		SimpleGUI::Slider(U"Value A", s0, 0.0, 100.0, Vec2(40, 384), 90, 310);
		SimpleGUI::Slider(U"Value B", s1, 0.0, 100.0, Vec2(40, 424), 90, 310, false);

		SimpleGUI::VerticalSlider(s2, 100.0, 0.0, Vec2(460, 40), 380);
		SimpleGUI::VerticalSlider(s3, 100.0, 0.0, Vec2(500, 40), 380, false);
	}
}
