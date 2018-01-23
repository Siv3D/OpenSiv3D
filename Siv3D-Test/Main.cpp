
# include <Siv3D.hpp>

void Main()
{
	const Audio audio(U"test.m4a");

	audio.play();

	while (System::Update())
	{

	}
}
