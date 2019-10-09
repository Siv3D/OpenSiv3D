# include <Siv3D.hpp>

void Main()
{
	Logger << U"Module: " << FileSystem::ModulePath();
	Logger << U"Initial: " << FileSystem::InitialDirectory();
	Logger << U"Current: " << FileSystem::CurrentDirectory();
	
	Logger << U"FullPath1: " << FileSystem::FullPath(U"../App/example/");
	Logger << U"FullPath2: " << FileSystem::FullPath(U"../App/example/windmill.png");
	Logger << U"Parent1: " << FileSystem::ParentPath(U"./");
	Logger << U"Parent2: " << FileSystem::ParentPath(U"example/windmill.png");
	Logger << U"Relative1: " << FileSystem::RelativePath(FileSystem::FullPath(U"../App/example/"));
	Logger << U"Relative2: " << FileSystem::RelativePath(FileSystem::FullPath(U"../App/example/windmill.png"));

	Print << U"Module: " << FileSystem::ModulePath();
	Print << U"Initial: " << FileSystem::InitialDirectory();
	Print << U"Current: " << FileSystem::CurrentDirectory();
	
	Print << U"FullPath1: " << FileSystem::FullPath(U"../App/example/");
	Print << U"FullPath2: " << FileSystem::FullPath(U"../App/example/windmill.png");
	Print << U"Parent1: " << FileSystem::ParentPath(U"./");
	Print << U"Parent2: " << FileSystem::ParentPath(U"example/windmill.png");
	Print << U"Relative1: " << FileSystem::RelativePath(FileSystem::FullPath(U"../App/example/"));
	Print << U"Relative2: " << FileSystem::RelativePath(FileSystem::FullPath(U"../App/example/windmill.png"));
	
	//const Texture texture(U"example/windmill.png");
	
    while (System::Update())
    {
		//texture.draw();
    }
}
