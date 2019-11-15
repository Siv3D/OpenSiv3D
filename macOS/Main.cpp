
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

struct FontSet
{
	SDFFont sdf;
	Font bitmap;
};

void Main()
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF(0.4, 0.5, 0.6));

	constexpr Vec2 pos(0, 0);
	const String text = U"OpenSiv3D\nあいうえおかきくけこ";

	{
		String s;
		for (auto i : Range(32, 126))
		{
			s << char32(i);
		}
		s += text;

		SDFFont(60, Typeface::Light).preload(s).saveGlyphs(U"sdf-font/light_60.png", U"sdf-font/light_60.json");
		SDFFont(60, Typeface::Heavy).preload(s).saveGlyphs(U"sdf-font/heavy_60.png", U"sdf-font/heavy_60.json");
	}

	const Array<FontSet> fontsets =
	{
		{ SDFFont({ U"sdf-font/light_60.png", U"sdf-font/light_60.json" }, 60, Typeface::Light), Font(60, Typeface::Light) },
		{ SDFFont({ U"sdf-font/heavy_60.png", U"sdf-font/heavy_60.json" }, 60, Typeface::Heavy), Font(60, Typeface::Heavy) },
	};

	size_t fontsetIndex = 0;
	size_t method = 0;
	double fontSize = 50;
	double outlineThreshold = 0.0;
	HSV outlineColor = Palette::White, innerColor = Palette::Black;

	while (System::Update())
	{
		const auto& fontset = fontsets[fontsetIndex];
		const int32 baseSize = fontset.sdf.baseSize();

		if (method == 0)
		{
			if (outlineThreshold > 0.0)
			{
				Graphics2D::SetSDFParameters(Float4(baseSize / 8.0, outlineThreshold, 0, 0));
				fontset.sdf(text).draw(fontSize, pos, outlineColor);
			}

			Graphics2D::SetSDFParameters(Float4(baseSize / 8.0, 0, 0, 0));
			fontset.sdf(text).draw(fontSize, pos, innerColor);
		}
		else if (method == 1)
		{
			Transformer2D tr(Mat3x2::Scale(fontSize / baseSize));
			fontset.bitmap(text).draw(pos, innerColor);
		}

		SimpleGUI::RadioButtons(fontsetIndex, { U"Light 60", U"Heavy 60"}, Vec2(20, 440), 150);
		SimpleGUI::RadioButtons(method, { U"SDFFont", U"Font" }, Vec2(20, 520), 150);
		SimpleGUI::Slider(U"size: {:.0f}"_fmt(fontSize), fontSize, 15, 550, Vec2(20, 600), 150, 200);
		SimpleGUI::Slider(U"outline: {:.2f}"_fmt(outlineThreshold), outlineThreshold, 0.0, 0.49, Vec2(20, 640), 150, 200, (method == 0));
		SimpleGUI::ColorPicker(outlineColor, Vec2(400, 560));
		SimpleGUI::ColorPicker(innerColor, Vec2(580, 560));
	}
}

