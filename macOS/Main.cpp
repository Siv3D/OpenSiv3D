
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	Print << FileSystem::FullPath(U"あいう/");
	
	while (System::Update())
	{
		if (KeyA.down())
		{
			Print << Dialog::SelectFolder();
		}
	}
}
