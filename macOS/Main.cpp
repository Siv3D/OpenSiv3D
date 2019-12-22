
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

void Main()
{
	Print << FileSystem::FullPath(U"example/");
	
	for (const auto& path : FileSystem::DirectoryContents(U"example/"))
	{
		Console << path;
	}
	
	while (System::Update())
	{
		if (KeyA.down())
		{
			Print << Dialog::SelectFolder();
		}
	}
}
