
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		LineString{{ 50, 50 },{ 200, 200 }, { 400, 200 },{ 100, 400 }}
			.drawCatmullRom(8.0, Palette::Pink, true);

		QuadraticBezier({ 200, 50 }, {400, 200 }, { 600, 50 })
			.draw(8.0, Palette::Red);
		
		CubicBezier({ 300, 400 }, { 450, 400 }, { 450, 100 }, { 600, 100 })
			.draw(8.0, Palette::Orange);
	}
}
