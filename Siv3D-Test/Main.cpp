# include <Siv3D.hpp>

ColorF Black(const Key& key)
{
	return key.pressed() ? ColorF(1.0, 0.8, 0.4) : ColorF(0.25);
}

ColorF PushE(const Key& key, const ColorF& color)
{
	return key.pressed() ? ColorF(1.0, 0.8, 0.4) : color;
}

void DrawJoyConL(const Vec2& pos, const JoyCon& joycon)
{
	const ColorF color(0.0, 0.75, 0.9);
	const Vec2 size(500, 180);
	const RectF base(pos, size);

	base.rounded(90).drawShadow(Vec2(0, -5), 30, 10, ColorF(0.0, 0.3));
	base.stretched(0, 0, -100, 0).draw(color);

	Circle(base.bl().movedBy(100, -100), 100).drawPie(180_deg, 90_deg, color);
	Circle(base.br().movedBy(-100, -100), 100).drawPie(90_deg, 90_deg, color);
	RectF(base.bl().movedBy(100, -100), 300, 100).draw(color);
	RectF(pos.movedBy(20, -10), 440, 10).draw(ColorF(0.25));

	Circle(base.bl().movedBy(100, -100), 100).drawArc(180_deg, 90_deg, 10, 10, Black(joycon.buttonLR));
	Circle(base.bl().movedBy(100, -100), 120).drawArc(220_deg, 50_deg, 10, 10, Black(joycon.buttonZLZR));

	RectF(Arg::center(pos.movedBy(50, 35)), 10, 40).draw(Black(joycon.buttonMinus));
	const Vec2 c = pos.movedBy(130, 90);
	Circle(c, 45).draw(Black(joycon.buttonStick));
	if (const auto d = joycon.povD8())
	{
		Circle(c + Circular(45, *d * 45_deg), 25).draw();
	}

	RectF(Arg::center(pos.movedBy(150, -10)), 50, 10).draw(PushE(joycon.buttonSL, color));
	RectF(Arg::center(pos.movedBy(350, -10)), 50, 10).draw(PushE(joycon.buttonSR, color));

	Circle(pos.movedBy(280, 50), 20).draw(Black(joycon.button3));
	Circle(pos.movedBy(240, 90), 20).draw(Black(joycon.button2));
	Circle(pos.movedBy(280, 130), 20).draw(Black(joycon.button0));
	Circle(pos.movedBy(320, 90), 20).draw(Black(joycon.button1));

	RectF(Arg::center(pos.movedBy(375, 55)), 30).draw(Black(joycon.buttonScreenshot));
}

void DrawJoyConR(const Vec2& pos, const JoyCon& joycon)
{
	const ColorF color(1.0, 0.4, 0.3);
	const Vec2 size(500, 180);
	const RectF base(pos, size);

	base.rounded(90).drawShadow(Vec2(0, -5), 30, 10, ColorF(0.0, 0.3));
	base.stretched(0, 0, -100, 0).draw(color);

	Circle(base.bl().movedBy(100, -100), 100).drawPie(180_deg, 90_deg, color);
	Circle(base.br().movedBy(-100, -100), 100).drawPie(90_deg, 90_deg, color);
	RectF(base.bl().movedBy(100, -100), 300, 100).draw(color);
	RectF(pos.movedBy(40, -10), 440, 10).draw(ColorF(0.25));

	Circle(base.br().movedBy(-100, -100), 100).drawArc(90_deg, 90_deg, 10, 10, Black(joycon.buttonLR));
	Circle(base.br().movedBy(-100, -100), 120).drawArc(90_deg, 50_deg, 10, 10, Black(joycon.buttonZLZR));

	Shape2D::Plus(20, 10, base.tr().movedBy(-50, 35)).draw(Black(joycon.buttonPlus));
	const Vec2 c = pos.movedBy(210, 90);
	Circle(c, 45).draw(Black(joycon.buttonStick));
	if (const auto d = joycon.povD8())
	{
		Circle(c + Circular(45, *d * 45_deg), 25).draw();
	}

	RectF(Arg::center(pos.movedBy(150, -10)), 50, 10).draw(PushE(joycon.buttonSL, color));
	RectF(Arg::center(pos.movedBy(350, -10)), 50, 10).draw(PushE(joycon.buttonSR, color));

	Circle(pos.movedBy(360, 50), 20).draw(Black(joycon.button3));
	Circle(pos.movedBy(320, 90), 20).draw(Black(joycon.button2));
	Circle(pos.movedBy(360, 130), 20).draw(Black(joycon.button0));
	Circle(pos.movedBy(400, 90), 20).draw(Black(joycon.button1));

	Circle(pos.movedBy(110, 55), 15).draw(Black(joycon.buttonHome));
}

void Main()
{
	Graphics::SetBackground(ColorF(0.9));

	Window::Resize(1280, 720);

	Vec2 left(200, 200), right(1000, 400);

	Effect effect;

	while (System::Update())
	{
		Window::SetTitle(Profiler::FPS());

		for (size_t i = 0; i < Gamepad.MaxUserCount; ++i)
		{
			if (JoyCon::IsJoyConL(Gamepad(i)))
			{
				const auto j = JoyCon(Gamepad(i));

				DrawJoyConL(Vec2(80, 480), j);

				if (auto d = j.povD8())
				{
					left += Circular(4, *d * 45_deg);
				}

				if (j.button2.down())
				{
					effect.add([center = left](double t) {
						Circle(center, 20 + t * 200).drawFrame(10, 0, AlphaF(1.0 - t));
						return t < 1.0;
					});
				}
			}
			else if (JoyCon::IsJoyConR(Gamepad(i)))
			{
				const auto j = JoyCon(Gamepad(i));

				DrawJoyConR(Vec2(700, 480), j);

				if (auto d = j.povD8())
				{
					right += Circular(4, *d * 45_deg);
				}

				if (j.button2.down())
				{
					effect.add([center = right](double t) {
						Circle(center, 20 + t * 200).drawFrame(10, 0, AlphaF(1.0 - t));
						return t < 1.0;
					});
				}
			}
		}

		Rect(40, 40, 1200, 400).draw(ColorF(0.1, 0.3, 0.2));

		Circle(left, 30).draw(ColorF(0.0, 0.75, 0.9));

		Circle(right, 30).draw(ColorF(1.0, 0.4, 0.3));

		effect.update();
	}
}
