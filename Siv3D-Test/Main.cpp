# include <Siv3D.hpp>

void Main()
{
	double r = 0.7, g = 0.8, b = 0.9, a = 1.0;

	while (System::Update())
	{
		SimpleGUI::Slider(U"R: {:.2f}"_fmt(r), r, Vec2(100, 40), 85, 120);
		SimpleGUI::Slider(U"G: {:.2f}"_fmt(g), g, Vec2(100, 80), 85, 120);
		SimpleGUI::Slider(U"B: {:.2f}"_fmt(b), b, Vec2(100, 120), 85, 120);
		SimpleGUI::Slider(U"A: {:.2f}"_fmt(a), a, Vec2(100, 160), 85, 200, false);

		if (SimpleGUI::Button(U"OK", Vec2(100, 200), 150))
		{
			Print << U"OK";
		}

		if (SimpleGUI::Button(U"キャンセル", Vec2(255, 200), 150))
		{
			Print << U"キャンセル";
		}

		if (SimpleGUI::Button(U"押せない", Vec2(100, 240), 120, false))
		{
			Print << U"押せない";
		}

		Graphics::SetBackground(ColorF(r, g, b));
	}
}
