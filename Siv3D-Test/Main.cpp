
# include <Siv3D.hpp>

void Main()
{
	Polygon polygon(Shape2D::NStar(10, 100, 80, Window::Center()));

	Serializer<MemoryWriter> w;

	w(polygon);

	Deserializer<ByteArray> b(w.getWriter().data(), w.getWriter().size());

	Polygon polygon2;

	b(polygon2);

	Print << (polygon.boundingRect() == polygon2.boundingRect());

	while (System::Update())
	{
		if (MouseL.pressed())
		{
			polygon.draw();
		}
		else
		{
			polygon2.draw();
		}
	}
}
