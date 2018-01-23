
# include <Siv3D.hpp>

void Main()
{
	BinaryReader reader(U"example/windmill.png");

	WritableMemoryMapping file(U"test.png");

	const int64 size = reader.size();

	file.map(0, size);

	reader.lookahead(file.data(), size);

	file.unmap();

	//const Audio audio(U"test.m4a");

	//audio.play();

	while (System::Update())
	{

	}
}
