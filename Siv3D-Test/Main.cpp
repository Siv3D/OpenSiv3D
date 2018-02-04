# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.9));
	Window::Resize(1280, 720);
	Effect effect;

	Vec2 left(640 - 100, 100), right(640 + 100, 100);
	double angle = 0_deg;
	double scale = 400.0;
	bool covered = true;

	while (System::Update())
	{
		scale += Mouse::Wheel() * -5;
		angle += 1_deg * MouseR.pressed() -1_deg * MouseL.pressed();
		if (KeyC.down())
			covered = !covered;

		Circle(Vec2(640 - 300, 450), scale / 2).drawFrame(scale * 0.1);
		Circle(Vec2(640 + 300, 450), scale / 2).drawFrame(scale * 0.1);

		for (size_t i = 0; i < Gamepad.MaxUserCount; ++i)
		{
			if (JoyCon::IsJoyConL(Gamepad(i)))
			{
				const auto joy = JoyCon(Gamepad(i));

				JoyConSymbol::DrawLAt(joy, Vec2(640-300, 450), scale, -90_deg - angle, covered);

				if (auto d = joy.povD8())
				{
					left += Circular(4, *d * 45_deg);
				}

				if (joy.button2.down())
				{
					effect.add([center = left](double t) {
						Circle(center, 20 + t * 200).drawFrame(10, 0, AlphaF(1.0 - t));
						return t < 1.0;
					});
				}
			}
			else if (JoyCon::IsJoyConR(Gamepad(i)))
			{
				const auto joy = JoyCon(Gamepad(i));

				JoyConSymbol::DrawRAt(joy, Vec2(640 + 300, 450), scale, 90_deg + angle, covered);

				if (auto d = joy.povD8())
				{
					right += Circular(4, *d * 45_deg);
				}

				if (joy.button2.down())
				{
					effect.add([center = right](double t) {
						Circle(center, 20 + t * 200).drawFrame(10, 0, AlphaF(1.0 - t));
						return t < 1.0;
					});
				}
			}
		}

		Circle(left, 30).draw(ColorF(0.0, 0.75, 0.9));
		Circle(right, 30).draw(ColorF(1.0, 0.4, 0.3));
		effect.update();
	}
}