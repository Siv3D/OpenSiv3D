
void Main()
{
	int32 n = 0;

	while (System::Update())
	{
		ClearPrint();

		Print << "Hello! " << n;

		Line line(Cursor::Pos(), Scene::Center());
		Line line2(300, 300, 500, 500);
		
		Optional<Vec2> o =line.intersectsAt(line2);

		if (o)
		{
			Print << o.value();
		}
		
		line2.draw(4);
		line.draw(4);

		Scene::SetBackground(HSV(++n * 0.5, 0.2, 1.0));
	}
}
