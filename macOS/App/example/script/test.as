
int Add(int a, int b)
{
	return a + b;
}

void PrintMessage()
{
	Print << "Hello, Siv3D!";
}

void DrawShapes()
{
	Rect(Arg::center(200, 300), 160).draw(ColorF(0.6, 0.8, 0.0));

	Circle(Scene::Center(), 80).draw(ColorF(0.0, 0.6, 0.8));

	Shape2D::Cross(100, 20, Vec2(600, 300)).draw(ColorF(0.8, 0.6, 0.6));
}
