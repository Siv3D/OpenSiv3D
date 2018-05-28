
# include <Siv3D.hpp> // OpenSiv3D v0.2.6

void Main()
{
	for (const auto& info : System::EnumerateWebcams())
	{
		Print << U"--";
		Print << info.index;
		Print << info.name;
		Print << info.uniqueName;
	}

	Webcam webcam(0);

	if (!webcam)
	{
		return;
	}

	Print << webcam.getResolution();

	//if (webcam.setResolution(Size(1280, 720)))
	//{
	//	Print << webcam.getResolution();
	//}

	webcam.start();

	DynamicTexture texture;

	while (System::Update())
	{
		if (webcam.hasNewFrame())
		{
			webcam.getFrame(texture);
		}

		if (texture)
		{
			texture.draw();
		}
	}
}
