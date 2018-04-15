
# include <Siv3D.hpp>

void Main()
{
	Print << AbsDiff(60, 100); // (uint32)40
	Print << AbsDiff(-0.5, -5.5); // 5.0
	Print << AbsDiff(INT_MIN, INT_MAX); // (uint32)4294967295

	while (System::Update())
	{

	}
}
