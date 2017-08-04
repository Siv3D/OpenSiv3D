# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Transition t0(0.2s, 0.5s), t1(0.2s, 0.1s);

	bool on = false;

	while (System::Update())
	{
		const RectF rect(Arg::center = Window::Center(), 100 + t0.easeInOut() * 50);

		t0.update(on);

		t1.update(rect.mouseOver());

		if (rect.draw(Palette::White.lerp(Palette::Skyblue, t1.value())).leftClicked())
		{
			on = !on;
		}
	}
}