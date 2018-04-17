
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		const Circle c(Cursor::Pos(), 80);

		if (Window::ClientRect().contains(c))
		{
			c.draw();
		}
	}
}
