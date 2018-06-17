
# include <Siv3D.hpp>

void Main()
{
	const Texture texture = Dialog::OpenTexture();

	const Audio audio = Dialog::OpenAudio();

	audio.play();

	while (System::Update())
	{
		texture.draw();
	}
}



