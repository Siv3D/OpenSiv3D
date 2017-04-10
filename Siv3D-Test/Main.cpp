
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	Log << EnumResourceFiles();

	Log << Resource(L"example/siv3d-kun.png");

	// 通常のファイルから
	Log << Image(L"example/siv3d-kun.png").size();

	// exe 埋め込みリソースから
	Log << Image(Resource(L"engine/siv3d-kun.png")).size();

	while (System::Update())
	{

	}
}
