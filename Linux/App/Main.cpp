# include <Siv3D.hpp> // OpenSiv3D v0.4.2

void Main()
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF(0.4, 0.5, 0.6));

	constexpr Vec2 pos(0, 0);
	const String text = U"OpenSiv3D\nあいうえお\nアイエウオ";

	/////////////////////
	//
	// 生成後はコメントアウト
	{
		String s;
		for (auto i : Range(32, 126))
		{
			s << char32(i);
		}
		s += text;

		// SDF の作成には時間がかかるので、
		// ASCII 文字と text をあらかじめ SDF 化して、フォント情報を保存しておく
		SDFFont(60, Typeface::Light).preload(s).saveGlyphs(U"sdf-font/light_60.png", U"sdf-font/light_60.json");
		SDFFont(60, Typeface::Heavy).preload(s).saveGlyphs(U"sdf-font/heavy_60.png", U"sdf-font/heavy_60.json");
		SDFFont(50, U"example/font/LogoTypeGothic/LogoTypeGothic.otf").preload(s).saveGlyphs(U"sdf-font/logo_50.png", U"sdf-font/logo_50.json");
	}
	/////////////////////

	// フォント情報から SDFFont を作成
	const Array<SDFFont> sdfFonts =
	{
		SDFFont({ U"sdf-font/light_60.png", U"sdf-font/light_60.json" }, 60, Typeface::Light),
		SDFFont({ U"sdf-font/heavy_60.png", U"sdf-font/heavy_60.json" }, 60, Typeface::Heavy),
		SDFFont({ U"sdf-font/logo_50.png", U"sdf-font/logo_50.json" }, 50, U"example/font/LogoTypeGothic/LogoTypeGothic.otf"),
	};

	const Array<Font> fonts =
	{
		Font(60, Typeface::Light),
		Font(60, Typeface::Heavy),
		Font(50, U"example/font/LogoTypeGothic/LogoTypeGothic.otf"),
	};

	size_t fontIndex = 0, method = 0;
	double fontSize = 80, outline1 = 0.0, outline2 = 0.0;
	HSV innerColor = Palette::Black, outlineColor = Palette::White;

	while (System::Update())
	{
		const auto& sdfFont = sdfFonts[fontIndex];
		const auto& font = fonts[fontIndex];
		const int32 baseSize = sdfFont.baseSize();

		if (method == 0)
		{
			Graphics2D::SetSDFParameters(sdfFont.pixelRange(), outline2);
			sdfFont(text).draw(fontSize, pos, innerColor);

			Graphics2D::SetSDFParameters(sdfFont.pixelRange(), outline1);
			sdfFont(text).draw(fontSize, pos, outlineColor);

			Graphics2D::SetSDFParameters(sdfFont.pixelRange());
			sdfFont(text).draw(fontSize, pos, innerColor);
		}
		else if (method == 1)
		{
			Transformer2D tr(Mat3x2::Scale(fontSize / baseSize));
			font(text).draw(pos, innerColor);
		}

		SimpleGUI::RadioButtons(fontIndex, { U"Light 60", U"Heavy 60", U"Logo 50" }, Vec2(20, 360), 150);
		SimpleGUI::RadioButtons(method, { U"SDFFont", U"Font" }, Vec2(20, 480), 150);
		SimpleGUI::Slider(U"size: {:.0f}"_fmt(fontSize), fontSize, 15, 550, Vec2(20, 560), 150, 200);
		SimpleGUI::Slider(U"outline1: {:.2f}"_fmt(outline1), outline1, 0.0, 0.49, Vec2(20, 600), 150, 200, (method == 0));
		SimpleGUI::Slider(U"outline2: {:.2f}"_fmt(outline2), outline2, 0.0, 0.49, Vec2(20, 640), 150, 200, (method == 0));
		SimpleGUI::ColorPicker(innerColor, Vec2(400, 560));
		SimpleGUI::ColorPicker(outlineColor, Vec2(580, 560));
	}
}
