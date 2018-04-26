//-----------------------------------------------
//
//	This file is part of the Siv3D HamFramework.
//
//	Copyright (c) 2014-2018 HAMSTRO
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D.hpp>

namespace s3d
{
	namespace JoyConSymbol
	{
		struct ButtonState
		{
			bool button0 = false;

			bool button1 = false;

			bool button2 = false;

			bool button3 = false;

			bool buttonSL = false;

			bool buttonSR = false;

			bool buttonMinus = false;

			bool buttonPlus = false;

			bool buttonStick = false;

			bool buttonHome = false;

			bool buttonScreenshot = false;

			bool buttonLR = false;

			bool buttonZLZR = false;

			Optional<int32> povD8;
		};

		inline void DrawLAt(const JoyCon& joycon, const ButtonState& guide, const Vec2& center, double _size, double angle = 0.0, bool covered = true, const ColorF& color = ColorF(0.0, 0.75, 0.9), const ColorF& colorPushed = ColorF(1.0, 0.8, 0.5), const ColorF& guideColor = ColorF(1.0, 0.7, 0.6), bool shadow = true)
		{
			const Vec2 size = (covered ? Vec2(6.9, 15.33) : Vec2(5.27, 15.33));
			const RectF base(Arg::center = center, size);
			const ColorF defaultButtonColor(0.3);
			const auto buttonColor = [=](const Key& key, bool guide) {
				return (key.pressed() ? colorPushed : guide ? guideColor : defaultButtonColor);
			};

			Transformer2D t(Mat3x2::Scale(1.0 / 15.33 * _size, center).rotated(angle, center));

			// shadow
			if (shadow)
			{
				if (covered)
				{
					base.stretched(-0.4).rounded(3.0).drawShadow(Circular(0.5, 180_deg - angle), 1.0, 0.5, ColorF(0.0, 0.3));
				}
				else
				{
					base.stretched(-0.3).rounded(2.7).drawShadow(Circular(0.5, 180_deg - angle), 1.0, 0.5, ColorF(0.0, 0.3));
				}
			}

			// body
			{
				Circle(base.tl().movedBy(3.0, 3.6), 3.0).drawPie(0_deg, -90_deg, color);
				RectF(base.tl().movedBy(0.0, 3.6), Vec2(3.0, 8.63)).draw(color);
				Circle(base.bl().movedBy(3.0, -3.1), 3.0).drawPie(180_deg, 90_deg, color);
				RectF(base.tl().movedBy(3.00, 0.6), Vec2(1.82, 14.63)).draw(color);
			}

			// arrow
			{
				const double delta = 1.15;
				const Vec2 c = base.tl().movedBy(2.55, 8.33);

				Circle(c.movedBy(-delta, 0), 0.55).draw(buttonColor(joycon.button0, guide.button0)); // left
				Circle(c.movedBy(0, delta), 0.55).draw(buttonColor(joycon.button1, guide.button1));  // down
				Circle(c.movedBy(0, -delta), 0.55).draw(buttonColor(joycon.button2, guide.button2)); // up
				Circle(c.movedBy(delta, 0), 0.55).draw(buttonColor(joycon.button3, guide.button3));  // right
			}

			// stick
			{
				const Vec2 c = base.tl().movedBy(2.55, 4.28);
				Circle(c, 1.2).draw(buttonColor(joycon.buttonStick, guide.buttonStick));

				if (const auto dg = guide.povD8)
				{
					Circle(c + Circular(1.2, *dg * 45_deg - 90_deg), 0.6).draw(guideColor);
				}

				if (const auto d = joycon.povD8())
				{
					Circle(c + Circular(1.2, *d * 45_deg + 90_deg), 0.6).draw();
				}
			}

			// Screenshot
			RoundRect(Arg::center = base.tl().movedBy(3.4, 11.13), Vec2(1.0, 1.0), 0.1).draw(buttonColor(joycon.buttonScreenshot, guide.buttonScreenshot));

			// Minus
			RectF(Arg::center = base.tl().movedBy(4.03, 2.0), Vec2(0.8, 0.2)).draw(buttonColor(joycon.buttonMinus, guide.buttonMinus));

			// L, ZL
			RectF(base.tl().movedBy(3.0, 0.4), Vec2(0.9, 0.4)).draw(buttonColor(joycon.buttonLR, guide.buttonLR));
			Circle(base.tl().movedBy(3.0, 3.6), 3.0).drawArc(0_deg, -68_deg, 0.2, 0.2, buttonColor(joycon.buttonLR, guide.buttonLR));
			RectF(base.tl().movedBy(3.0, 0.0), Vec2(0.9, 0.4)).draw(buttonColor(joycon.buttonZLZR, guide.buttonZLZR));
			Circle(base.tl().movedBy(3.0, 3.6), 3.2).drawArc(0_deg, -30_deg, 0.0, 0.4, buttonColor(joycon.buttonZLZR, guide.buttonZLZR));

			if (covered)
			{
				// strap body
				Circle(base.tr().movedBy(-2.08, 2.33), 1.73).drawPie(0_deg, 90_deg, defaultButtonColor);
				RectF(base.tr().movedBy(-2.08, 2.33), Vec2(1.73, 11.0 + 0.17)).draw(defaultButtonColor);
				Circle(base.br().movedBy(-2.08, -2.0 + 0.17), 1.73).drawPie(90_deg, 90_deg, defaultButtonColor);

				// SL, SR
				RoundRect(base.tr().moveBy(-0.45, 3.1), Vec2(0.45, 2.0), 0.1).draw(buttonColor(joycon.buttonSL, guide.buttonSL));
				RoundRect(base.tr().moveBy(-0.45, 9.0), Vec2(0.45, 2.0), 0.1).draw(buttonColor(joycon.buttonSR, guide.buttonSR));
			}
			else
			{
				const auto buttonColor2 = [=](const Key& key, bool guide) {
					return (key.pressed() ? colorPushed : guide ? guideColor : color);
				};

				// SL, SR
				RectF(base.tr().movedBy(-0.45, 2.0), Vec2(0.3, 11.33)).draw(defaultButtonColor);
				RoundRect(base.tr().movedBy(-0.3, 3.5), Vec2(0.3, 1.2), 0.1).draw(buttonColor2(joycon.buttonSL, guide.buttonSL));
				RoundRect(base.tr().movedBy(-0.3, 9.4), Vec2(0.3, 1.2), 0.1).draw(buttonColor2(joycon.buttonSR, guide.buttonSR));
			}
		}

		inline void DrawLAt(const JoyCon& joycon, const Vec2& center, double _size, double angle = 0.0, bool covered = true, const ColorF& color = ColorF(0.0, 0.75, 0.9), const ColorF& colorPushed = ColorF(1.0, 0.8, 0.5), const ColorF& guideColor = ColorF(1.0, 0.7, 0.6), bool shadow = true)
		{
			DrawLAt(joycon, ButtonState(), center, _size, angle, covered, color, colorPushed, guideColor, shadow);
		}

		inline void DrawRAt(const JoyCon& joycon, const ButtonState& guide, const Vec2& center, double _size, double angle = 0.0, bool covered = true, const ColorF& color = ColorF(1.0, 0.4, 0.3), const ColorF& colorPushed = ColorF(1.0, 0.8, 0.5), const ColorF& guideColor = ColorF(1.0, 0.7, 0.6), bool shadow = true)
		{
			const Vec2 size = (covered ? Vec2(6.9, 15.33) : Vec2(5.27, 15.33));
			const RectF base(Arg::center = center, size);
			const ColorF defaultButtonColor(0.3);
			const auto buttonColor = [=](const Key& key, bool guide) {
				return (key.pressed() ? colorPushed : guide ? guideColor : defaultButtonColor);
			};

			Transformer2D t(Mat3x2::Scale(1.0 / 15.33 * _size, center).rotated(angle, center));

			// shadow
			if (shadow)
			{
				if (covered)
				{
					base.stretched(-0.4).rounded(3.0).drawShadow(Circular(0.5, 180_deg - angle), 1.0, 0.5, ColorF(0.0, 0.3));
				}
				else
				{
					base.stretched(-0.3).rounded(2.7).drawShadow(Circular(0.5, 180_deg - angle), 1.0, 0.5, ColorF(0.0, 0.3));
				}
			}

			// body
			{
				Circle(base.tr().movedBy(-3.0, 3.6), 3.0).drawPie(0_deg, 90_deg, color);
				RectF(base.tr().movedBy(-3.0, 3.6), Vec2(3.0, 8.63)).draw(color);
				Circle(base.br().movedBy(-3.0, -3.1), 3.0).drawPie(180_deg, -90_deg, color);
				RectF(base.tr().movedBy(-4.82, 0.6), Vec2(1.82, 14.63)).draw(color);
			}

			// ABXY
			{
				const double delta = 1.15;
				const Vec2 c = base.tr().movedBy(-2.55, 4.28);

				Circle(c.movedBy(delta, 0), 0.55).draw(buttonColor(joycon.button0, guide.button0));  // A
				Circle(c.movedBy(0, -delta), 0.55).draw(buttonColor(joycon.button1, guide.button1)); // X
				Circle(c.movedBy(0, delta), 0.55).draw(buttonColor(joycon.button2, guide.button2));  // B
				Circle(c.movedBy(-delta, 0), 0.55).draw(buttonColor(joycon.button3, guide.button3)); // Y
			}

			// stick
			{
				const Vec2 c = base.tr().movedBy(-2.55, 8.33);
				Circle(c, 1.2).draw(buttonColor(joycon.buttonStick, guide.buttonStick));

				if (const auto dg = guide.povD8)
				{
					Circle(c + Circular(1.2, *dg * 45_deg - 90_deg), 0.6).draw(guideColor);
				}

				if (const auto d = joycon.povD8())
				{
					Circle(c + Circular(1.2, *d * 45_deg - 90_deg), 0.6).draw();
				}
			}

			// Home
			Circle(base.tr().movedBy(-3.4, 11.13), 0.55).draw(buttonColor(joycon.buttonHome, guide.buttonHome));

			// Plus
			Shape2D::Plus(0.4, 0.2, base.tr().movedBy(-4.03, 2.0)).draw(buttonColor(joycon.buttonPlus, guide.buttonPlus));

			// R, ZR
			RectF(base.tr().movedBy(-3.9, 0.4), Vec2(0.9, 0.4)).draw(buttonColor(joycon.buttonLR, guide.buttonLR));
			Circle(base.tr().movedBy(-3.0, 3.6), 3.0).drawArc(0_deg, 68_deg, 0.2, 0.2, buttonColor(joycon.buttonLR, guide.buttonLR));
			RectF(base.tr().movedBy(-3.9, 0.0), Vec2(0.9, 0.4)).draw(buttonColor(joycon.buttonZLZR, guide.buttonZLZR));
			Circle(base.tr().movedBy(-3.0, 3.6), 3.2).drawArc(0_deg, 30_deg, 0.0, 0.4, buttonColor(joycon.buttonZLZR, guide.buttonZLZR));

			if (covered)
			{
				// strap body
				Circle(base.tl().movedBy(2.08, 2.33), 1.73).drawPie(0_deg, -90_deg, defaultButtonColor);
				RectF(base.tl().movedBy(0.35, 2.33), Vec2(1.73, 11.0 + 0.17)).draw(defaultButtonColor);
				Circle(base.bl().movedBy(2.08, -2.0 + 0.17), 1.73).drawPie(180_deg, 90_deg, defaultButtonColor);

				// SL, SR
				RoundRect(base.tl().moveBy(0.0, 3.1), Vec2(0.45, 2.0), 0.1).draw(buttonColor(joycon.buttonSR, guide.buttonSR));
				RoundRect(base.tl().moveBy(0.0, 9.0), Vec2(0.45, 2.0), 0.1).draw(buttonColor(joycon.buttonSL, guide.buttonSL));
			}
			else
			{
				const auto buttonColor2 = [=](const Key& key, bool guide) {
					return (key.pressed() ? colorPushed : guide ? guideColor : color);
				};

				// SL, SR
				RectF(base.tl().movedBy(0.15, 2.0), Vec2(0.3, 11.33)).draw(defaultButtonColor);
				RoundRect(base.tl().movedBy(0.0, 3.5), Vec2(0.3, 1.2), 0.1).draw(buttonColor2(joycon.buttonSR, guide.buttonSR));
				RoundRect(base.tl().movedBy(0.0, 9.4), Vec2(0.3, 1.2), 0.1).draw(buttonColor2(joycon.buttonSL, guide.buttonSL));
			}
		}

		inline void DrawRAt(const JoyCon& joycon, const Vec2& center, double _size, double angle = 0.0, bool covered = true, const ColorF& color = ColorF(1.0, 0.4, 0.3), const ColorF& colorPushed = ColorF(1.0, 0.8, 0.5), const ColorF& guideColor = ColorF(1.0, 0.7, 0.6), bool shadow = true)
		{
			DrawRAt(joycon, ButtonState(), center, _size, angle, covered, color, colorPushed, guideColor, shadow);
		}
	}
}

/* example

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

*/
