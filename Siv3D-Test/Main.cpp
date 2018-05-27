
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

	while (System::Update())
	{

	}
}
