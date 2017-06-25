# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	Circle c(320, 240, 20);

	while (System::Update())
	{
		Circle(Cursor::PreviousPosF(), 40).draw(Palette::Gray);

		Circle(Cursor::PosF(), 40).draw();

		c.moveBy(Cursor::DeltaF());

		c.draw();
	}
}
