
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		Window::SetTitle(Cursor::Pos());
	}
}
