
# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.8, 0.9, 1.0));

	Window::Resize(1280, 720);

	const Polygon poly = Shape2D::Star(300, Window::Center(), 40);

	const Font font(50, Typeface::Heavy);

	const Polygon icon = ImageProcessing::FindExternalContour(Icon::LoadImage(0xf072, 140), true).simplified().movedBy(-70, -70);

	while (System::Update())
	{
		String s;
		
		if (MouseL.pressed())
		{
			const Polygon circle = icon.movedBy(Cursor::Pos());

			poly.draw();

			const bool i = poly.intersects(circle);

			MicrosecClock m;
			const bool c = poly.contains(circle);
			//m.print();
			circle.draw(c ? Palette::Red : i ? Palette::Orange : Palette::Green);

			if (i)
				s += U"交差";

			if (c)
				s += U"\n包含";
		}
		else
		{
			const Circle circle(Cursor::Pos(), 60);

			poly.draw();

			const bool i = poly.intersects(circle);
			//MicrosecClock m;
			const bool c = poly.contains(circle);
			//m.print();

			circle.draw(c ? Palette::Red : i ? Palette::Orange : Palette::Green);

			if (const auto points = circle.intersectsAt(poly))
			{
				for (const auto& p : points.value())
				{
					Circle(p, 8).draw(ColorF(0.25));
				}
			}

			if (i)
				s += U"交差";

			if (c)
				s += U"\n包含";
		}

		font(s).draw(240, 80, ColorF(0.25));
	}
}
