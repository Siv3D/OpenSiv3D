
# include <Siv3D.hpp> // OpenSiv3D v0.2.3

void Main()
{
	Graphics::SetBackground(ColorF(1.0, 0.9, 0.7));

	Window::Resize(640, 560);

	const Image image(U"example/siv3d-kun.png");

	const Texture texture(image);

	const Polygon polygon = ImageProcessing::FindExternalContour(image, true).movedBy(150, 30);

	const Polygon convex = polygon.calculateConvexHull();

	const Polygon largeConvex = convex.calculateBuffer(20);

	Image shadowImage(Window::Size(), Color(255, 0));

	convex.calculateBuffer(10).movedBy(10, 10).overwrite(shadowImage, ColorF(255));

	const Texture shadow(shadowImage.gaussianBlurred(40, 40));

	while (System::Update())
	{
		shadow.draw(ColorF(0.0, 0.5));

		largeConvex.draw(ColorF(0.96, 0.98, 1.0));

		texture.draw(150, 30);
	}
}