
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

struct SDFParameters
{
	float a = 0.0f, b = 0.0f, c = 0.0f, d = 0.0f;
};

void Main()
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF(0.2, 0.6, 0.4));
	//const Font fontO(80);
	const Font font2(42, Typeface::Bold);
	font2.getGlyphs(U"ABCy-._");
	Logger << U"------";
	const SDFFont font(42, Typeface::Bold);
	font.getGlyphs(U"ABCy-._");

	const PixelShader ps(U"sdf" SIV3D_SELECT_SHADER(U".hlsl", U".frag"),
		{ { U"PSConstants2D", 0 }, { U"SDFParameters", 1 } });

	const PixelShader psOutline(U"sdfOutline" SIV3D_SELECT_SHADER(U".hlsl", U".frag"),
		{ { U"PSConstants2D", 0 }, { U"SDFParameters", 1 } });

	if (!ps)
	{
		throw Error(U"!ps");
	}

	if (!psOutline)
	{
		throw Error(U"!psOutline");
	}

	// 定数バッファ
	ConstantBuffer<SDFParameters> cb;

	double scale = 1.0;
	double p_a = 1.0, p_b = 0.3;
	bool outlineMode = true;

	HSV outlineColor = Palette::Black;
	HSV innerColor = Palette::White;

	while (System::Update())
	{
		cb->a = 40 * float(p_a) * 0.5f;
		cb->b = float(p_b);
		Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);

		if (MouseR.pressed())
		{
			font.getTexture().scaled(scale).draw();
		}
		else
		{
			//if (outlineMode)
			//{
			//	ScopedCustomShader2D shader(psOutline);
			//	font.getTexture().scaled(scale).draw(outlineColor);
			//}

			if (MouseL.pressed())
			{
				ScopedCustomShader2D shader(ps);
				//font.getTexture().scaled(scale).draw(innerColor);

				Transformer2D tr(Mat3x2::Scale(scale));

				Vec2 penPos(5, 5);

				for (const auto& glyph : font.getGlyphs(U"OpenSiv3D 実装会"))
				{
					glyph.texture.draw(penPos + glyph.offset - Vec2(5, 5), Palette::Black);
					penPos.x += glyph.xAdvance;
				}
			}
			else
			{
				Vec2 penPos(5, 5);

				for (const auto& glyph : font2.getGlyphs(U"OpenSiv3D y.,_-"))
				{
					glyph.texture.draw(penPos + glyph.offset, Palette::Black);
					penPos.x += glyph.xAdvance;
				}
			}
		}

		//fontO(U"拡大").draw(Cursor::Pos(), ColorF(1,0,0,0.5));

		SimpleGUI::Slider(U"scale", scale, 0.1, 20.0, Vec2(100, 600), 80, 200);
		SimpleGUI::Slider(U"p_a", p_a, 0.1, 10.0, Vec2(100, 640), 80, 200);
		SimpleGUI::CheckBox(outlineMode, U"outline", Vec2(400, 600));
		SimpleGUI::Slider(U"p_b", p_b, 0.277, 0.51, Vec2(400, 640), 80, 200);
		SimpleGUI::ColorPicker(outlineColor, Vec2(700, 460));
		SimpleGUI::ColorPicker(innerColor, Vec2(700, 580));
	}
}
