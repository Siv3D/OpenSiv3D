
# include <Siv3D.hpp>

void Main()
{
	const Texture texture(L"example/windmill.png");

	while (System::Update())
	{
		//texture.rotate(30_deg).drawAt(Cursor::Pos()).drawFrame(0, 2);

		QuadraticBezier bezier(Vec2(20, 20), Cursor::Pos(), Vec2(400, 400));

		CubicBezier cb(Vec2(100, 400), Vec2(300, 400), Vec2(300, 100), Vec2(500,100));

		Circle(bezier.p0, 10).drawFrame();
		Circle(bezier.p1, 10).drawFrame();
		Circle(bezier.p2, 10).drawFrame();

		bezier.draw(4);

		cb.draw(4);
	}
}
