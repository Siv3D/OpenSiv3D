
# include <Siv3D.hpp>

class Item
{
private:

	Texture m_texture;

	Polygon m_polygon;

	Polygon m_convex;

	Polygon m_largeConvex;

	Vec2 m_pos = Vec2(0, 0);

	double m_angle = 0.0;

	bool m_isSmall = false;

public:

	Item() = default;

	Item(const Image& image, const Vec2& pos, double angle)
		: m_texture(image)
		, m_pos(pos)
		, m_angle(angle)
		, m_isSmall(image.width() < 200)
	{
		m_polygon = ImageProcessing::FindExternalContour(image, true);

		m_polygon.moveBy(-image.size() / 2);

		m_polygon.rotate(angle);

		m_polygon.moveBy(image.size() / 2);

		m_convex = m_polygon.calculateConvexHull();

		m_largeConvex = m_convex.calculateBuffer(m_isSmall ? 10 : 20);
	}

	void writeShadow(Image& image) const
	{
		m_convex.calculateBuffer(m_isSmall ? 4 : 8).overwrite(image, m_pos + Vec2(5, 5), Color(255));
	}

	void draw(double t) const
	{
		if (6.0 < t)
		{
			m_largeConvex.draw(m_pos, ColorF(0.96, 0.98, 1.0));
		}

		if (1 < t)
		{
			m_texture.rotated(m_angle).draw(m_pos);
		}

		if (InRange(t, 2.0, 6.0))
		{
			m_polygon.drawFrame(m_pos, 6, Palette::Red);
		}

		if (InRange(t, 3.0, 6.0))
		{
			m_convex.drawFrame(m_pos, 6, Palette::Green);
		}

		if (InRange(t, 5.0, 6.0))
		{
			m_largeConvex.drawWireframe(m_pos, 1, Palette::Blue);
		}

		if (InRange(t, 4.0, 6.0))
		{
			m_largeConvex.drawFrame(m_pos, 6, Palette::Purple);
		}
	}
};

void Main()
{
	Window::Resize(800, 600);

	Image shadowImage(Window::Size(), Color(255, 0));

	Graphics::SetBackground(ColorF(1.0, 0.9, 0.7));

	Array<Item> items;
	items << Item(Image(U"example/siv3d-kun.png"), Vec2(230, 40), 0_deg);
	items << Item(Emoji::LoadImage(U"🐈"), Vec2(60, 60), -10_deg);
	items << Item(Emoji::LoadImage(U"🐤"), Vec2(550, 190), 0_deg);
	items << Item(Emoji::LoadImage(U"🎧"), Vec2(620, 60), 0_deg);
	items << Item(Emoji::LoadImage(U"🍰"), Vec2(60, 400), 20_deg);
	items << Item(Emoji::LoadImage(U"🔥"), Vec2(650, 340), 10_deg);
	items << Item(Emoji::LoadImage(U"🏆"), Vec2(50, 220), 20_deg);

	for (const auto& item : items)
	{
		item.writeShadow(shadowImage);
	}

	const Texture texture(shadowImage.gaussianBlurred(25, 25));

	Stopwatch s(true);

	while (System::Update())
	{
		if (KeyS.down())
			s.restart();

		if (s > 7s)
		{
			texture.draw(ColorF(0.0, 0.4));
		}

		for (const auto& item : items)
		{
			item.draw(s.sF());
		}
	}
}
