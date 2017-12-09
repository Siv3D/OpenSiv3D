
# include <Siv3D.hpp>
# include "Test/Test.hpp"

void Main()
{
	const Font font(30);

	constexpr size_t k = sizeof(TextureID);

	Print(sizeof(TextureID));

	while (System::Update())
	{
		//Print << System::FrameCount();

		//font(U"Siv3D").draw();
	}
}
