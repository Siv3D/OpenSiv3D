# include <Siv3D.hpp> // OpenSiv3D v0.4.1

void Main()
{
	const Font font(120);

	while (System::Update())
	{
		const int32 i = Scene::FrameCount();

		if (4 <= i)
		{
			return;
		}

		font(i).draw();
		ScreenCapture::SaveCurrentFrame(U"Screenshot/{}.png"_fmt(i));		
	}
}
