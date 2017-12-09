
# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "Test/Test.hpp"

void Main()
{
	const Font font(30);

	constexpr size_t k = sizeof(TextureID);

	Print(sizeof(TextureID));

	while (System::Update())
	{
		Rect(Arg::center(Window::Center()), 200, 100).scaled(1.0 + Cursor::Pos().x / 100.0).draw();

		//Print << System::FrameCount();

		//font(U"Siv3D").draw();
	}
}
