
# include <Siv3D.hpp> // OpenSiv3D v0.2.5

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

	//webcam.start();

	while (System::Update())
	{

	}
}
