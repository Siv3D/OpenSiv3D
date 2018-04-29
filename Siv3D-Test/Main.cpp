
# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	VideoWriter writer;
	
	Print << writer.open(U"test.mp4", Size(1280, 720), 60.0);

	Image image(1280, 720);

	for (auto i : step(640))
	{
		image.fill(Palette::White);

		Rect(0, 300, i*2, 100).overwrite(image, HSV(i));

		writer.writeFrame(image);
	}

	while (System::Update())
	{

	}
}
