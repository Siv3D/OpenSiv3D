# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.25));

	Polygon polygon;

	int32 shapeIndex = 0;

	while (System::Update())
	{
		if (MouseR.down())
		{
			++shapeIndex %= 3;
		}

		polygon.drawFrame(7, Palette::Orange);

		polygon.draw(ColorF(0.8, 0.9, 1.0));

		{
			RenderStateBlock2D wireframe(RasterizerState::WireframeCullNone);

			polygon.draw();
		}

		polygon.boundingRect().drawFrame(2, Palette::Lightgreen);

		polygon.computeConvexHull().drawFrame(4, Palette::Yellow);

		if (shapeIndex == 0)
		{
			const Rect rect(Arg::center(Cursor::Pos()), 80);

			rect.drawFrame(2, Palette::Red);

			if (MouseL.down())
			{
				polygon.append(rect.asPolygon());
			}
		}
		else if (shapeIndex == 1)
		{
			const Shape2D shape = Shape2D::Plus(60, 40, Cursor::Pos());

			shape.drawFrame(2, Palette::Red);

			if (MouseL.down())
			{
				polygon.append(Polygon(shape));
			}
		}
		else 
		{
			const Shape2D shape = Shape2D::Star(60, Cursor::Pos());

			shape.drawFrame(2, Palette::Red);

			if (MouseL.down())
			{
				polygon.append(Polygon(shape));
			}
		}
	}
}