
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

void Main()
{
	Texture texture;

	Log << texture.isEmpty();

	Log << EnumResourceFiles();

	Log << Resource(L"example/siv3d-kun.png");

	// 通常のファイルから
	Log << Image(L"example/siv3d-kun.png").size();

	// exe 埋め込みリソースから
	Log << TextReader(Resource(L"engine/engine.txt")).readAll();

	while (System::Update())
	{

	}
}
