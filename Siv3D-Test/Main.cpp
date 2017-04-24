# include <Siv3D.hpp>

void Main()
{
	EasingController<Vec2> easing(
		Easing::Quint,
		Vec2(80, 100),	// 始点
		Vec2(560, 100),	// 終点
		1000ms			// 時間
	);

	while (System::Update())
	{
		if (MouseL.down())
		{
			easing.start();
		}

		if (MouseR.down())
		{
			easing.setB(Vec2(560, 200));
		}

		if (KeyA.down())
		{
			easing.jumpToA();
		}

		if (KeyB.down())
		{
			easing.jumpToB();
		}

		Circle(easing.base(), 20).draw(Palette::Orange);

		Circle(easing.easeInOut(), 20).moveBy(0, 80).draw();

		Circle(easing.easeIn(), 20).moveBy(0, 160).draw();

		Circle(easing.easeOut(), 20).moveBy(0, 240).draw();
	}
}