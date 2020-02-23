
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	while (System::Update())
	{
		Rect(50, 50, 300)
			.drawFrame(20, Palette::Orange, Palette::White);

		Circle(200, 200, 100)
			.drawPie(0_deg, 120_deg, Palette::Orange, Palette::White);

		Circle(400, 200, 100)
			.drawArc(0_deg, 120_deg, 10, 10, Palette::Orange, Palette::White);
	}
}
