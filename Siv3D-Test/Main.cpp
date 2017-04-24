# include <Siv3D.hpp>

void Main()
{
	const BlendState b;

	Log << b.enable;
	Log << b.alphaToCoverageEnable;

	while (System::Update())
	{
		Rect(20).draw();

		Rect(100, 100, 100).drawFrame(20, 0);

		Circle(200, 200, 40).drawFrame(20, 0, Palette::Orange);

		Circle(Cursor::Pos(), 100).drawFrame(40, 0, Palette::Blue, Palette::White);
	}
}