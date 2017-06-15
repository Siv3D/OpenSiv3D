# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.7, 0.9, 0.5));

	const Font font(20);
	TextBox textbox(font, 30, 30, 260, L"", L"数式 例: sin(x)");
	
	double x = 0.0;
	MathParser parser;
	parser.setVaribale(L"x", &x);
	LineString lines(640);

	while (System::Update())
	{
		textbox.update();
		parser.setExpression(textbox.getText());

		for (auto i : step(640))
		{
			x = (i - 320) / 40.0;
			lines[i].set(i, 240 - parser.evalOr(0.0) * 40.0);
		}

		Line(0, 240, 640, 240).draw(Palette::Gray);
		Line(320, 0, 320, 480).draw(Palette::Gray);
		lines.draw(1, Palette::Black);
		textbox.draw();
	}
}
