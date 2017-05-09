# include <Siv3D.hpp>

void Main()
{
	LineString lines;

	while (System::Update())
	{
		if (!Cursor::Delta().isZero())
		{
			lines << Cursor::Pos();

			Log << lines;
		}

		lines.draw(10);
	}
}
