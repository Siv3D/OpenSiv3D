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
	
	Logger << U"Exists: " << FileSystem::Exists(U"example/windmill.png");
	Logger << U"IsDirectory: " << FileSystem::IsDirectory(U"example/windmill.png");
	Logger << U"IsFile: " << FileSystem::IsFile(U"example/windmill.png");
	Logger << U"IsResource: " << FileSystem::IsResource(U"example/windmill.png");
	//Logger << U"NativePath: " << FileSystem::NativePath(U"example/windmill.png");
	Logger << U"Extension: " << FileSystem::Extension(U"example/windmill.png");
	Logger << U"FileName: " << FileSystem::FileName(U"example/windmill.png");
	Logger << U"BaseName: " << FileSystem::BaseName(U"example/windmill.png");
	Logger << U"VolumePath: " << FileSystem::VolumePath(U"example/windmill.png");
	Logger << U"IsEmptyDirectory: " << FileSystem::Exists(U"example/");
	//Logger << U"Size: " << FileSystem::Size(U"example/"); //permision
	//Logger << U"Size: " << FileSystem::Size(U"example/windmill.png"); //permision
	Logger << U"FileSize: " << FileSystem::FileSize(U"example/windmill.png");
	Logger << U"CreationTime: " << FileSystem::CreationTime(U"example/windmill.png");
	Logger << U"WriteTime: " << FileSystem::WriteTime(U"example/windmill.png");
	Logger << U"AccessTime: " << FileSystem::AccessTime(U"example/windmill.png");
	//Logger << U"DirectoryContents: " << FileSystem::DirectoryContents(U"example/svm/");
	Logger << U"SpecialFolderPath: " << FileSystem::SpecialFolderPath(SpecialFolder::Pictures);
	Logger << U"SpecialFolderPath: " << FileSystem::SpecialFolderPath(SpecialFolder::Caches);
	Logger << U"TemporaryDirectoryPath: " << FileSystem::TemporaryDirectoryPath();
	Logger << U"UniqueFilePath: " << FileSystem::UniqueFilePath();
	Logger << U"CreateDirectories: " << FileSystem::CreateDirectories(U"test1/aaa/");
	Logger << U"CreateParentDirectories: " << FileSystem::CreateParentDirectories(U"test2/bbb/a.png");
	
	Print << U"Module: " << FileSystem::ModulePath();
	Print << U"Initial: " << FileSystem::InitialDirectory();
	Print << U"Current: " << FileSystem::CurrentDirectory();
	Print << U"FullPath1: " << FileSystem::FullPath(U"../App/example/");
	Print << U"FullPath2: " << FileSystem::FullPath(U"../App/example/windmill.png");
	Print << U"Parent1: " << FileSystem::ParentPath(U"./");
	Print << U"Parent2: " << FileSystem::ParentPath(U"example/windmill.png");
	Print << U"Relative1: " << FileSystem::RelativePath(FileSystem::FullPath(U"../App/example/"));
	Print << U"Relative2: " << FileSystem::RelativePath(FileSystem::FullPath(U"../App/example/windmill.png"));

	const Texture texture(U"example/windmill.png");

    while (System::Update())
    {
		texture.draw();
    }
}
