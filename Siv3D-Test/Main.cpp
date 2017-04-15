
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		for (auto p : step({ 10, 10 }))
		{
			Rect(p * 40, 38).draw(HSV(10 * (p.x + p.y)));
		}
	}
}
