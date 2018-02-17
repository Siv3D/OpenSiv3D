
# include <Siv3D.hpp>

void Main()
{
	const Texture texture1(U"example/windmill.png");
	
	const Texture texture2(Resource(U"engine/texture/box-shadow/128.png"));
	
	Print << U"Current:\n" << FileSystem::CurrentPath();
	
	Print << U"App:\n" << FileSystem::ModulePath();
	
	Print << U"texture1:\n" << FileSystem::FullPath(U"example/windmill.png");
	
	Print << U"texture2:\n" << Resource(U"picture/windmill2.png");
	
	while (System::Update())
	{
		texture1(0, 0, 100, 100).draw(0, 0);
		
		texture2(0, 0, 100, 100).draw(100, 0);
	}
}
