# include <Siv3D.hpp> // OpenSiv3D v0.1.6

void Main()
{
	Print << FileSystem::DirectoryContents(L"e");

	Print << FileSystem::DirectoryContents(L"example");

	Print << FileSystem::DirectoryContents(L"example/");

	while (System::Update())
	{	

	}
}
