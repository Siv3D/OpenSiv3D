
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	Scene::SetBackground(ColorF(0.33, 0.32, 0.31));

	Array<Rect> rects;

	for (auto p : step(Size(3, 4)))
	{
		rects << Rect(p * Size(220, 140), 180, 100).movedBy(80, 40);
	}

	while (System::Update())
	{
		rects[0].rounded(30, 0, 0, 0).draw(HSV(20, 0.75, 1.0));
		rects[1].rounded(30, 30, 0, 0).draw(HSV(40, 0.75, 1.0));
		rects[2].rounded(0, 30, 0, 0).draw(HSV(60, 0.75, 1.0));

		rects[3].rounded(30, 0, 0, 30).draw(HSV(80, 0.75, 1.0));
		rects[4].rounded(10, 20, 30, 40).draw(HSV(100, 0.75, 1.0));
		rects[5].rounded(0, 30, 30, 0).draw(HSV(120, 0.75, 1.0));

		rects[6].rounded(100, 0, 0, 0).draw(HSV(140, 0.75, 1.0));
		rects[7].rounded(100, 0, 100, 0).draw(HSV(160, 0.75, 1.0));
		rects[8].rounded(0, 0, 100, 0).draw(HSV(180, 0.75, 1.0));

		rects[9].rounded(100, 0, 0, 20).draw(HSV(200, 0.75, 1.0));
		rects[10].rounded(100, 20, 100, 20).draw(HSV(220, 0.75, 1.0));
		rects[11].rounded(0, 20, 100, 0).draw(HSV(240, 0.75, 1.0));
	}
}
