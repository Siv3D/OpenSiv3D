# include <Siv3D.hpp> // OpenSiv3D v0.1.6

void Main()
{
	const Audio audio(L"test.wav");

	audio.play();

	while (System::Update())
	{	
		if (Key1.down())
		{
			audio.play(0.1s);
		}

		if (Key2.down())
		{
			audio.pause(1s);
		}

		if (Key3.down())
		{
			audio.stop(1s);
		}
	}
}
