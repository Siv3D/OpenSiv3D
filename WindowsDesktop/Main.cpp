
# define SIV3D_CONCURRENT
# include <Siv3D.hpp>

void Main()
{
	double p0 = 1.0, p1 = 0.4, p2 = 0.5;
	HSV c0 = Palette::Red;
	size_t index = 0;

	while (System::Update())
	{
		if (KeyA.pressed())
		{
			SimpleGUI::Headline(U"設定", Vec2(20, 20));
			SimpleGUI::Headline(U"空の色", Vec2(240, 20));
			SimpleGUI::Headline(U"マップ", Vec2(420, 20));
		}

		if (KeyB.pressed())
		{
			SimpleGUI::Headline(U"設定", Vec2(20, 20),200);
			SimpleGUI::Headline(U"空の色", Vec2(240, 20),160);
			SimpleGUI::Headline(U"マップ", Vec2(420, 20),120);
		}

		SimpleGUI::Slider(U"明るさ", p0, Vec2(20, 60));
		SimpleGUI::Slider(U"広さ", p1, Vec2(20, 100));
		SimpleGUI::Slider(U"頑丈さ", p2, Vec2(20, 140));

		SimpleGUI::ColorPicker(c0, Vec2(240, 60));

		SimpleGUI::RadioButtons(index, { U"草原", U"丘陵", U"山岳" }, Vec2(420, 60), 120);
	}
}
