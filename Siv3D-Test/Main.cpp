
# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	int32 n = 0;
	
	while (System::Update())
	{
		if (MouseL.down())
		{
			n = Random(-99999, 99999);
		}
		
		SevenSegment::DrawText(Format(n).lpad(6), Vec2(20, 20), 70, 8, 4, 10, ColorF(0, 1, 0), ColorF(0.25));
	}
}
