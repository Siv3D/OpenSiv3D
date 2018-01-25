# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(160, 200, 100));

	//GUI guiControlloer(GUIStyle::Default);
	//guiControlloer.addln(L"Controller", GUIRadioButton::Create(
	//	{ L"1P", L"2P", L"3P", L"4P" }, 0u));
	//guiControlloer.addln(GUIText::Create(L"DeadZone"));
	//guiControlloer.addln(L"DeadZone", GUICheckBox::Create({ L"óLå¯" }));

	//GUI guiVib(GUIStyle::Default);
	//guiVib.addln(GUIText::Create(L"êUìÆÅ@í·é¸îg | çÇé¸îg"));
	//guiVib.add(L"left", GUISlider::Create(0.0, 1.0, 0.0, 100));
	//guiVib.addln(L"right", GUISlider::Create(0.0, 1.0, 0.0, 100));
	//guiVib.setPos(210, 40);

	const Ellipse buttonLB(160, 140, 50, 24);
	const Ellipse buttonRB(520, 140, 50, 24);

	const RectF leftTrigger(150, 16, 40, 100);
	const RectF rightTrigger(500, 16, 40, 100);

	const Circle buttonLThumb(170, 250, 35);
	const Circle buttonRThumb(420, 350, 35);
	const Circle buttonDPad(260, 350, 40);

	const Circle buttonA(510, 300, 20);
	const Circle buttonB(560, 250, 20);
	const Circle buttonX(460, 250, 20);
	const Circle buttonY(510, 200, 20);
	const Circle buttonBack(270, 250, 15);
	const Circle buttonStart(410, 250, 15);

	while (System::Update())
	{
		const unsigned userIndex = 0;// guiControlloer.radioButton(L"Controller").checkedItem.value();
		auto controller = XInput(userIndex);

		//if (guiControlloer.checkBox(L"DeadZone").checked(0))
		{
			controller.setLeftTriggerDeadZone();
			controller.setRightTriggerDeadZone();
			controller.setLeftThumbDeadZone();
			controller.setRightThumbDeadZone();
		}
		//else
		//{
		//	controller.setLeftTriggerDeadZone(DeadZone::None);
		//	controller.setRightTriggerDeadZone(DeadZone::None);
		//	controller.setLeftThumbDeadZone(DeadZone::None);
		//	controller.setRightThumbDeadZone(DeadZone::None);
		//}

		const double lv = 0; //guiVib.slider(L"left").value;
		const double rv = 0;// guiVib.slider(L"right").value;
		controller.setVibration(lv, rv);

		buttonLB.draw(Color(controller.buttonLB.pressed() ? 255 : 200));
		buttonRB.draw(Color(controller.buttonRB.pressed() ? 255 : 200));

		Ellipse(340 + 3.0 * Random(lv + rv), 480, 300, 440).draw(Color(232));
		Ellipse(340, 40, 220, 120).draw(Color(160, 200, 100));
		Circle(340, 660, 240).draw(Color(160, 200, 100));

		Circle(340, 250, 30).draw(Color(160));

		if (controller.isConnected())
		{
			Circle(340, 250, 32).drawPie(-0.5_pi + 0.5_pi * controller.userIndex, 0.5_pi, Color(200, 255, 120));
		}

		Circle(340, 250, 25).draw(Color(140));

		leftTrigger.draw(Alpha(64));
		leftTrigger.stretched((controller.leftTrigger - 1.0) * leftTrigger.h, 0, 0, 0).draw();

		rightTrigger.draw(Alpha(64));
		rightTrigger.stretched((controller.rightTrigger - 1.0) * rightTrigger.h, 0, 0, 0).draw();

		buttonLThumb.draw(Color(controller.buttonLThumb.pressed() ? 220 : 127));
		Circle(buttonLThumb.center + Vec2(controller.leftThumbX, -controller.leftThumbY) * 25, 20).draw();
		if (const auto d = controller.leftThumbD8())
		{
			const Vec2 v = Circular(1, *d * 45_deg);
			Line(buttonLThumb.center + v * buttonLThumb.r, buttonLThumb.center + v * (buttonLThumb.r + 20)).drawArrow(3, Vec2(8, 8), Palette::Orange);
		}

		buttonRThumb.draw(Color(controller.buttonRThumb.pressed() ? 220 : 127));
		Circle(buttonRThumb.center + Vec2(controller.rightThumbX, -controller.rightThumbY) * 25, 20).draw();
		if (const auto d = controller.rightThumbD8())
		{
			const Vec2 v = Circular(1, *d * 45_deg);
			Line(buttonRThumb.center + v * buttonRThumb.r, buttonRThumb.center + v * (buttonRThumb.r + 20)).drawArrow(3, Vec2(8, 8), Palette::Orange);
		}

		buttonDPad.draw(Color(127));

		const Vec2 direction(
			controller.buttonRight.pressed() - controller.buttonLeft.pressed(),
			controller.buttonDown.pressed() - controller.buttonUp.pressed());

		if (!direction.isZero())
		{
			Circle(buttonDPad.center + direction.normalized() * 25, 15).draw();
		}

		buttonA.draw(Color(0, 255, 64).setA(controller.buttonA.pressed() ? 255 : 64));
		buttonB.draw(Color(255, 0, 64).setA(controller.buttonB.pressed() ? 255 : 64));
		buttonX.draw(Color(0, 64, 255).setA(controller.buttonX.pressed() ? 255 : 64));
		buttonY.draw(Color(255, 127, 0).setA(controller.buttonY.pressed() ? 255 : 64));

		buttonBack.draw(Color(controller.buttonBack.pressed() ? 255 : 200));
		buttonStart.draw(Color(controller.buttonStart.pressed() ? 255 : 200));
	}
}
